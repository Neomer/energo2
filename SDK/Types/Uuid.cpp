//
// Created by vinokurov on 04.12.2019.
//

#include "Uuid.h"

using namespace energo::types;

Uuid::Uuid() {

}

bool Uuid::equals(const Uuid &other) const {
    return true;
}

bool Uuid::operator==(const Uuid &other) const {
    return equals(other);
}
