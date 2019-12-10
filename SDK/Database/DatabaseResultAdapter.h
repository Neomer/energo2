//
// Created by vinokurov on 10.12.2019.
//

#ifndef ENERGO_DATABASERESULTADAPTER_H
#define ENERGO_DATABASERESULTADAPTER_H

#include <vector>
#include <string>
#include <string_view>
#include "SqlValue.h"

namespace energo::db {

class EXPORTS DatabaseResultAdapter {
public:
    DatabaseResultAdapter() = default;

    virtual ~DatabaseResultAdapter() = default;

    [[nodiscard]] virtual int getRowsCount() const = 0;

    [[nodiscard]] virtual int getFieldsCount() const = 0;

    virtual void getFieldNames(std::vector<std::string> &fields) const = 0;

    [[nodiscard]] virtual bool isValid() const = 0;

    [[nodiscard]] virtual int getFieldIndexByName(std::string_view name) const = 0;

    [[nodiscard]] virtual SqlValue value(int fieldIndex, int rowIndex) const = 0;

    virtual void close() = 0;
};

}


#endif //ENERGO_DATABASERESULTADAPTER_H
