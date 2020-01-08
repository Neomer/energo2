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
    explicit Button(std::string_view label);
    explicit Button(std::string_view label, const std::function<void()> &clickedListener);
    
    void setOnClickListener(const std::function<void()> &listener);
};

}

#endif //ENERGO_BUTTON_H
