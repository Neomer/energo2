//
// Created by kir on 08.12.2019.
//

#include <date/date.h>
#include <date/tz.h>
#include <fmt/chrono.h>
#include <fmt/ostream.h>
#include <fmt/format.h>
#include <sstream>
#include "DateTime.h"

using namespace std;
using namespace std::chrono;
using namespace energo::types;
using namespace date;
using namespace fmt;

DateTime DateTime::Now() {
    DateTime dt;
    dt._timePoint = floor<seconds>(system_clock::now());
    return dt;
}

DateTime::DateTime() {
    setDate(1970, 1, 1);
}

DateTime::DateTime(int year, int month, int day) {
    setDate(year, month, day);
}

void DateTime::setDate(int year, int month, int day) {
    auto dt = date::year{year}/month/day;
    _timePoint = floor<seconds>(days{2});
}

std::string DateTime::toString() const {
    stringstream stream;
    stream << _timePoint;
    return stream.str();
}

