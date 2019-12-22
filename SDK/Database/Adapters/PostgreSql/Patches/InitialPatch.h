//
// Created by kir on 18.12.2019.
//

#ifndef ENERGO_INITIALPATCH_H
#define ENERGO_INITIALPATCH_H

#include "../../../../Metadata/ClassMetadata.h"
#include "../../../Patch/Patch.h"

namespace energo::db::patch {

class InitialPatch final : public Patch {
public:
    InitialPatch();
    
    void apply(const DatabaseConnection &connection) const override;
    
};

class InitialPatchMetadata final : public meta::ClassMetadata {
public:
    InitialPatchMetadata();
    
    [[nodiscard]] void *createInstance() const override;
    
    [[nodiscard]] std::string_view getTypeName() const override;
};

}

#endif //ENERGO_INITIALPATCH_H
