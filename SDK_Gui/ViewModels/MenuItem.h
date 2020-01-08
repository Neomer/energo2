//
// Created by kir on 08.01.2020.
//

#ifndef ENERGO_MENUITEM_H
#define ENERGO_MENUITEM_H

#include <memory>
#include <vector>
#include <string>
#include <string_view>

namespace energo::ui::models {

class MenuItem {
    std::vector<std::shared_ptr<MenuItem>> _subItems;
    std::string _text;
    
public:
    explicit MenuItem(std::string_view text);
    
    MenuItem(std::string_view text, std::vector<std::shared_ptr<MenuItem>> subItems);
    
    void append(const std::shared_ptr<MenuItem>& item);
    
    [[nodiscard]] inline const std::vector<std::shared_ptr<MenuItem>> &subItems() const { return _subItems; }
    
    [[nodiscard]] inline bool hasSubItems() const {
        return !_subItems.empty();
    }
    
    [[nodiscard]] std::string_view text() const { return _text; }
};

}

#endif //ENERGO_MENUITEM_H
