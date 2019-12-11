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

    [[nodiscard]] int getRowsCount() const override;

    [[nodiscard]] int getFieldsCount() const override;

    void getFieldNames(std::vector<const char *> &fields) const override;

    [[nodiscard]] bool isValid() const override;

    [[nodiscard]] int getFieldIndexByName(std::string_view name) const override;

    [[nodiscard]] SqlValue value(int fieldIndex, int rowIndex) const override;
    
    bool any() const override;
    
    void close() override;
};

}

#endif //ENERGO_POSTGRESQLRESULTADAPTER_H
