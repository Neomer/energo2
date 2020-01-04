//
// Created by kir on 18.12.2019.
//

#ifndef ENERGO_SINGLETONCLASSMETADATA_H
#define ENERGO_SINGLETONCLASSMETADATA_H

#include "ClassMetadata.h"

namespace energo::meta {

class EXPORTS SingletonClassMetadata : public ClassMetadata {
    void *_instance;

public:
    SingletonClassMetadata(const types::Uuid &typeUid, const types::Uuid &parentTypeUid);
    
    void setInstance(void *instance);
    
    [[nodiscard]] void *createInstance() const final;
    
    [[nodiscard]] void *createInstance();
    
    [[nodiscard]] bool isReady() const;

protected:
    [[nodiscard]] virtual void *createInstanceInternal() const = 0;
};

}

#endif //ENERGO_SINGLETONCLASSMETADATA_H
