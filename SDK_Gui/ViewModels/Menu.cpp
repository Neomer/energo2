//
// Created by kir on 07.01.2020.
//

#include "Menu.h"

using namespace std;
using namespace energo::ui::models;

Menu::Menu(const std::initializer_list<std::shared_ptr<MenuItem>> &items)
{
    _items.reserve(items.size());
    for (auto &item : items) {
        _items.push_back(item);
    }
}
