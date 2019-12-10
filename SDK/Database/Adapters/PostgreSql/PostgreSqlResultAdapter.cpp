//
// Created by vinokurov on 10.12.2019.
//

#include <cinttypes>
#include "PostgreSqlResultAdapter.h"

using namespace std;
using namespace energo::db::adapters;

PostgreSqlResultAdapter::PostgreSqlResultAdapter(PGresult *result, const TransformationProvider &transformationProvider):
    _result{result},
    _transformationProvider{transformationProvider}
{

}

PostgreSqlResultAdapter::~PostgreSqlResultAdapter() {
    close();
}

int PostgreSqlResultAdapter::getRowsCount() const {
    return PQntuples(_result);
}

int PostgreSqlResultAdapter::getFieldsCount() const {
    return PQnfields(_result);
}

void PostgreSqlResultAdapter::getFieldNames(std::vector<std::string> &fields) const {
    fields.clear();
    auto length = getFieldsCount();
    for (auto idx = 0; idx < length; ++idx) {
        fields.emplace_back(PQfname(_result, idx));
    }
}

bool PostgreSqlResultAdapter::isValid() const {
    auto status = PQresultStatus(_result);
    return status != PGRES_BAD_RESPONSE && status != PGRES_FATAL_ERROR;
}

int PostgreSqlResultAdapter::getFieldIndexByName(std::string_view name) const {
    return PQfnumber(_result, _transformationProvider.EscapeFieldNameIfNeeded(name).c_str());
}

energo::db::SqlValue PostgreSqlResultAdapter::value(int fieldIndex, int rowIndex) const {
    return SqlValue(PQgetvalue(_result, fieldIndex, rowIndex));
}

void PostgreSqlResultAdapter::close() {
    PQclear(_result);
}

