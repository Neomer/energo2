//
// Created by kir on 18.12.2019.
//

#ifndef ENERGO_PATCH_H
#define ENERGO_PATCH_H

#include "../../global.h"
#include "../DatabaseConnectionProvider.h"

namespace energo::db {

/**
 * Патч базы данных.
 */
class EXPORTS Patch {
    const types::Uuid &_patchUid, &_prevPatchUid, &_databaseTypeUid;
    
public:
    Patch(const types::Uuid &patchUid, const types::Uuid &prevPatchUid, const types::Uuid &databaseTypeUid);
    
    virtual ~Patch() = default;
    
    /**
     * @return Uuid патча.
     */
    [[nodiscard]] const types::Uuid &getPatchUid() const;
    
    /**
     * @return Uuid предыдущего патча
     */
    [[nodiscard]] const types::Uuid &getPreviousPatchUid() const;
    
    /**
     * Проверяет совместимость патча с указанной базой данных.
     * @param provider Провайдер подключений к базе данных.
     * @return
     */
    //[[nodiscard]] bool isSupported(const DatabaseConnectionProviderMetadata *providerMetadata) const;
    
    
    /**
     * Применить патч к базе данных.
     * @param connection Подключение к базе данных.
     */
    virtual void apply(const DatabaseConnection &connection) const = 0;
    
};

}

#endif //ENERGO_PATCH_H
