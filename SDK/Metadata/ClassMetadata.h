//
// Created by vinokurov on 11.12.2019.
//

#ifndef ENERGO_CLASSMETADATA_H
#define ENERGO_CLASSMETADATA_H

#include "TypeMetadata.h"
#include "MetaClass.h"

namespace energo::meta {

class MetadataProvider;

/**
 * Метаданные класса.
 */
class EXPORTS ClassMetadata: public TypeMetadata {
    energo::types::Uuid _parentTypeUid;

public:
    ClassMetadata(const types::Uuid &typeUid, const types::Uuid &parentTypeUid);

    [[nodiscard]] const types::Uuid &getParentTypeUid() const;
    
    /**
     * Проверяет является ли данный класс наследником указанного типа.
     * @param typeUid Тип родительского класса.
     * @return
     */
    [[nodiscard]] bool isDerived(const types::Uuid &typeUid) const;
    
    /**
     * Рекурсивно проверяет является ли данный класс, либо его родительские классы наследником указанного типа.
     * @param typeUid Идентификатор типа.
     * @param metadataProvider Провайдер метаданных.
     * @return
     */
    [[nodiscard]] bool isDerived(const types::Uuid &typeUid, const MetadataProvider &metadataProvider) const;

    /**
     * @return Создает новый инстанс класса.
     */
    [[nodiscard]] virtual MetaClass *createInstance() const = 0;
};

}

#endif //ENERGO_CLASSMETADATA_H
