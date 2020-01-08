//
// Created by kir on 08.01.2020.
//

#ifndef ENERGO_TEXTBOX_H
#define ENERGO_TEXTBOX_H

#include <string_view>
#include "Widget.h"

namespace energo::ui {

class EXPORTS TextBox : public Widget {
public:
    TextBox();
    
    TextBox &setText(std::string_view text);
    
    [[nodiscard]] std::string_view text() const;
};

}

#endif //ENERGO_TEXTBOX_H
