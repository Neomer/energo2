//
// Created by kir on 08.12.2019.
//

#ifndef ENERGO_SQLVALUE_H
#define ENERGO_SQLVALUE_H

#include <cinttypes>
#include <string_view>
#include "../os.h"
#include "../Types/Uuid.h"

namespace energo::db {

class EXPORTS SqlValue final {
public:
    explicit SqlValue(std::string_view data);
    
    /**
     * @return Значение в виде целого 8-битного беззнакового.
     * @throws std::invalid_argument Не удалось привести к типу.
     */
    [[nodiscard]] uint8_t asUInt8() const;
    
    /**
     * @return Значение в виде целого 16-битного беззнакового.
     * @throws std::invalid_argument Не удалось привести к типу.
     */
    [[nodiscard]] uint16_t asUInt16() const;
    
    /**
     * @return Значение в виде целого 32-битного беззнакового.
     * @throws std::invalid_argument Не удалось привести к типу.
     */
    [[nodiscard]] uint32_t asUInt32() const;
    
    /**
     * @return Значение в виде целого 8-битного.
     * @throws std::invalid_argument Не удалось привести к типу.
     */
    [[nodiscard]] int8_t asInt8() const;
    
    /**
     * @return Значение в виде целого 16-битного.
     * @throws std::invalid_argument Не удалось привести к типу.
     */
    [[nodiscard]] int16_t asInt16() const;
    
    /**
     * @return Значение в виде целого 32-битного.
     * @throws std::invalid_argument Не удалось привести к типу.
     */
    [[nodiscard]] int32_t asInt32() const;
    
    /**
     * @return Значение в виде вещественного 32-битного.
     * @throws std::invalid_argument Не удалось привести к типу.
     */
    [[nodiscard]] float_t asFloat() const;
    
    /**
     * @return Значение в виде целого целого 64-битного.
     * @throws std::invalid_argument Не удалось привести к типу.
     */
    [[nodiscard]] double_t asDouble() const;

#ifdef ENVIRONMENT64
    
    /**
     * @return Значение в виде целого 64-битного беззнакового.
     * @throws std::invalid_argument Не удалось привести к типу.
     */
    [[nodiscard]] uint64_t asUint64() const;
    
    /**
     * @return Значение в виде целого 64-битного беззнакового.
     * @throws std::invalid_argument Не удалось привести к типу.
     */
    [[nodiscard]] int64_t asInt64() const;
    
#endif
    
    /**
     * @return Значение в виде строки.
     * @throws std::invalid_argument Не удалось привести к типу.
     */
    [[nodiscard]] std::string asString() const;
    
    /**
     * @return Значение в виде UUID.
     * @throws std::invalid_argument Не удалось привести к типу.
     */
    [[nodiscard]] energo::types::Uuid asUuid() const;
    
    /**
     * @return Значение в виде логического значения.
     * @throws std::invalid_argument Не удалось привести к типу.
     */
    [[nodiscard]] bool asBool() const;

private:
    std::string _data;
    size_t _length;
};

}

#endif //ENERGO_SQLVALUE_H
