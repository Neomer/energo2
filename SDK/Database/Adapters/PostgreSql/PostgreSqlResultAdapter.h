//
// Created by vinokurov on 10.12.2019.
//

#ifndef ENERGO_POSTGRESQLRESULTADAPTER_H
#define ENERGO_POSTGRESQLRESULTADAPTER_H

#include <libpq-fe.h>
#include "../../DatabaseResultAdapter.h"
#include "../../TransformationProvider.h"

namespace energo::db::adapters {

class EXPORTS PostgreSqlResultAdapter final: public DatabaseResultAdapter {
    PGresult *_result;
    const TransformationProvider &_transformationProvider;
public:
    explicit PostgreSqlResultAdapter(PGresult *result, const TransformationProvider &transformationProvider);
    ~PostgreSqlResultAdapter() override;

    int getRowsCount() const override;

    int getFieldsCount() const override;

    void getFieldNames(std::vector<std::string> &fields) const override;

    bool isValid() const override;

    int getFieldIndexByName(std::string_view name) const override;

    SqlValue value(int fieldIndex, int rowIndex) const override;

    void close() override;
};

}

#endif //ENERGO_POSTGRESQLRESULTADAPTER_H
