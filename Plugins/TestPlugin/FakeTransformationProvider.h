//
// Created by kir on 16.12.2019.
//

#ifndef ENERGO_FAKETRANSFORMATIONPROVIDER_H
#define ENERGO_FAKETRANSFORMATIONPROVIDER_H

#include "../../SDK/Database/TransformationProvider.h"

namespace energo::db::adapters {

class EXPORTS FakeTransformationProvider : public TransformationProvider {
public:
    [[nodiscard]] std::string escapeFieldNameIfNeeded(std::string_view fieldName) const override;
    
    [[nodiscard]] std::string escapeTableNameIfNeeded(std::string_view tableName) const override;
};

}

#endif //ENERGO_FAKETRANSFORMATIONPROVIDER_H
