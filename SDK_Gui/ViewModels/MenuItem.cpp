//
// Created by kir on 08.01.2020.
//

#include "MenuItem.h"

#include <utility>

using namespace std;
using namespace energo::ui::models;

MenuItem::MenuItem(std::string_view text) :
    _text{text}
{

}

MenuItem::MenuItem(std::string_view text, std::vector<std::shared_ptr<MenuItem>> subItems) :
        _text{text},
        _subItems{std::move(subItems)}
{

}

void MenuItem::append(const shared_ptr<MenuItem>& item) {
    _subItems.push_back(item);
}

