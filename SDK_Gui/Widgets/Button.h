//
// Created by kir on 07.01.2020.
//

#ifndef ENERGO_BUTTON_H
#define ENERGO_BUTTON_H

#include <string_view>
#include "Widget.h"

namespace energo::ui {

class EXPORTS Button : public Widget {
public:
    Button();
    
    Button &label(std::string_view label);
};

}

#endif //ENERGO_BUTTON_H
