//
// Created by kir on 07.01.2020.
//

#ifndef ENERGO_ACTIONBAR_H
#define ENERGO_ACTIONBAR_H

#include <memory>
#include <string_view>
#include <vector>
#include "../ViewModels/Menu.h"
#include "ActionItem.h"

namespace energo::ui {

class EXPORTS ActionBar : public Widget {
    std::vector<std::shared_ptr<ActionItem>> _actions;
    
public:
    ActionBar();
    explicit ActionBar(const models::Menu &menu);
    
    ActionBar &action(std::string_view label);
    ActionBar &action(ActionItem *item);
    
    void show() override;
    
    void hide() override;
};

}

#endif //ENERGO_ACTIONBAR_H
