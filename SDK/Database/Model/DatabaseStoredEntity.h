//
// Created by vinokurov on 09.12.2019.
//

#ifndef ENERGO_DATABASESTOREDENTITY_H
#define ENERGO_DATABASESTOREDENTITY_H

#include <vector>
#include <utility>
#include <string_view>
#include "../TransformationProvider.h"
#include "../SqlQueryReader.h"
#include "../../Metadata/MetaClass.h"

namespace energo::db::entity {

class EXPORTS DatabaseStoredEntity {
public:
    using TFieldValuePairList = std::vector<std::pair<std::string, std::string>>;
    
    explicit DatabaseStoredEntity() = default;

    virtual void fromSql(const SqlQueryReader &reader) = 0;
    
    virtual void toSqlValues(TFieldValuePairList &fieldValueList, const TransformationProvider &transformationProvider) const = 0;
    
    /**
     * Возвращает форматированное для SQL-запроса значение поля по имени колонки в таблице базы данных.
     * @param fieldHash Хэш-сумма имени колонки.
     * @param transformationProvider Провайдер трансформаций для базы данных.
     * @return
     * @throws std::invalid_argument Колонка с указанной хэш-суммой не содержится в сущности данного типа.
     */
    [[nodiscard]] virtual std::string getFieldValue(size_t fieldHash, const TransformationProvider &transformationProvider) const = 0;
};

}


#endif //ENERGO_DATABASESTOREDENTITY_H
