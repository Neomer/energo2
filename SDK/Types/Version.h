//
// Created by kir on 15.12.2019.
//

#ifndef ENERGO_VERSION_H
#define ENERGO_VERSION_H

#include <cinttypes>
#include <string_view>
#include <ostream>
#include "../global.h"

namespace energo::types {

class EXPORTS Version final {
    uint16_t _major, _minor;
    uint32_t _patch, _build;

public:
    static bool TryParse(std::string_view version, Version &result);
    
    static Version Parse(std::string_view version);
    
    Version();
    Version(uint16_t major, uint16_t minor, uint32_t patch, uint32_t build);
    
    [[nodiscard]] uint16_t getMajor() const;
    
    void setMajor(uint16_t major);
    
    [[nodiscard]] uint16_t getMinor() const;
    
    void setMinor(uint16_t minor);
    
    [[nodiscard]] uint32_t getPatch() const;
    
    void setPatch(uint32_t patch);
    
    [[nodiscard]] uint32_t getBuild() const;
    
    void setBuild(uint32_t build);
    
    [[nodiscard]] std::string toString() const;
    
    friend std::ostream &operator<<(std::ostream &os, const Version &version) {
        os << version.toString();
        return os;
    }
};

}

#endif //ENERGO_VERSION_H
