//
// Created by kir on 08.12.2019.
//

#ifndef ENERGO_DATETIME_H
#define ENERGO_DATETIME_H

#include <chrono>
#include <string>
#include <ostream>
#include "../global.h"

namespace energo::types {

class EXPORTS DateTime {
public:
    static DateTime Now();
    
    DateTime();
    DateTime(int year, int month, int day);
    ~DateTime() = default;
    
    void setDate(int year, int month, int day);

    [[nodiscard]] std::string toString() const;
    
    friend std::ostream &operator<<(std::ostream &os, const DateTime &dateTime) {
        os << dateTime.toString();
        return os;
    }

private:
    std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds> _timePoint;
};

}

#endif //ENERGO_DATETIME_H
