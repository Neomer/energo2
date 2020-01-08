//
// Created by kir on 07.01.2020.
//

#ifndef ENERGO_MENU_H
#define ENERGO_MENU_H


#include "MenuItem.h"

namespace energo::ui::models {

class Menu {
    std::vector<std::shared_ptr<MenuItem>> _items;

public:
    Menu() = default;
    
    Menu(const std::initializer_list<std::shared_ptr<MenuItem>> &items);
    
    [[nodiscard]] inline const std::vector<std::shared_ptr<MenuItem>> &getItems() const { return _items; }
};

}

#endif //ENERGO_MENU_H
