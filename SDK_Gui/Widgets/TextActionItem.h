//
// Created by kir on 07.01.2020.
//

#ifndef ENERGO_TEXTACTIONITEM_H
#define ENERGO_TEXTACTIONITEM_H

#include <string_view>
#include "ActionItem.h"

namespace energo::ui {

class EXPORTS TextActionItem : public ActionItem {
public:
    explicit TextActionItem(std::string_view label);
};

}

#endif //ENERGO_TEXTACTIONITEM_H
