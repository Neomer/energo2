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
#include <ostream>

namespace energo::types {

/**
 * Класс для работы с Uuid.
 */
class EXPORTS Uuid final {
public:
    Uuid();

#ifdef ENVIRONMENT64
    explicit Uuid(const uint64_t *data);
    Uuid(uint64_t p1, uint64_t p2);
#else
    explicit Uuid(const uint32_t *data);
    Uuid(uint32_t p1, uint32_t p2, uint32_t p3, uint32_t p4);
#endif


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
     * Преобразует UUID  в строку вида xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx.
     * @return
     */
    [[nodiscard]] std::string toString() const;

    /**
     * Проверяет на равенство два UUID.
     * @param other UUID для сравнения.
     * @return
     */
    [[nodiscard]] bool equals(const Uuid &other) const;

    bool operator==(const Uuid &other) const;
    
    bool operator!=(const Uuid &other) const;
    
    friend std::ostream &operator<<(std::ostream &os, const Uuid &uuid) {
        os << uuid.toString();
        return os;
    }

private:
#ifdef ENVIRONMENT64
    uint64_t _data[2]{};
#else
    uuint32_t _data[4];
#endif
};

}

#endif //ENERGO_UUID_H
