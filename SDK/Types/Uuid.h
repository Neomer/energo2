//
// Created by vinokurov on 04.12.2019.
//

#ifndef ENERGO_UUID_H
#define ENERGO_UUID_H

#include "../os.h"
#include "../global.h"
#include <cinttypes>

namespace energo::types {

/**
 * Класс для работы с Uuid.
 */
class EXPORTS Uuid final {
public:
    /**
     * Формирует пустой Uuid {00000000-0000-0000-0000-000000000000}
     */
    static Uuid Empty();
    /**
     * Формирует случайный Uuid.
     */
    static Uuid Random();

    [[nodiscard]] bool equals(const Uuid &other) const;

    bool operator==(const Uuid &other) const;

private:
    Uuid();

#ifdef ENVIRONMENT64
    uint64_t _data[2];
#else
    uuint32_t _data[4];
#endif
};

}

#endif //ENERGO_UUID_H
