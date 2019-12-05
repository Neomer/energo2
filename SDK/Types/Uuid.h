//
// Created by vinokurov on 04.12.2019.
//

#ifndef ENERGO_UUID_H
#define ENERGO_UUID_H

#include "../os.h"
#include "../global.h"
#include <cinttypes>
#include <string>
#include <string_view>
#include <random>

namespace energo::types {

/**
 * Класс для работы с Uuid.
 */
class EXPORTS Uuid final {
    friend class Uuid_Tests;

public:
    Uuid();

    /**
     * Формирует пустой Uuid {00000000-0000-0000-0000-000000000000}
     */
    static Uuid Empty();

    /**
     * Формирует случайный Uuid.
     */
    static Uuid Random(std::random_device &rd);

    /**
     * Пытается преобразовать строку в класс UUID.
     * @param data Входная строка.
     * @param uid Возвращаемый UUID.
     * @return Удалось ли преобразовать входную строку в класс.
     */
    static bool TryParse(std::string_view data, Uuid &uid);

    /**
     * Преобразовывает строку в класс UUID.
     * @param data Входная строка.
     * @return Преобразованный UUID.
     * @throws std::invalid_argument - не удалось преобразовать входную строку.
     */
    static Uuid Parse(std::string_view data);

    /**
     * Преобразует UUID  в строку вида XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX.
     * @return
     */
    [[nodiscard]] std::string toString() const;

    [[nodiscard]] bool equals(const Uuid &other) const;

    bool operator==(const Uuid &other) const;

private:
#ifdef ENVIRONMENT64
    uint64_t _data[2];
#else
    uuint32_t _data[4];
#endif
};

}

#endif //ENERGO_UUID_H
