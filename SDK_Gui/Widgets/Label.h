//
// Created by kir on 08.01.2020.
//

#ifndef ENERGO_LABEL_H
#define ENERGO_LABEL_H

#include <string_view>
#include "Widget.h"

namespace energo::ui {

class Label : public Widget {
public:
    explicit Label(std::string_view text);
};

}

#endif //ENERGO_LABEL_H
