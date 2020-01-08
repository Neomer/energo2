//
// Created by kir on 07.01.2020.
//

#include <gtkmm.h>
inline Gtk::MenuItem *cast(void *instance) {
    return reinterpret_cast<Gtk::MenuItem *>(instance);
}

#include "TextActionItem.h"

energo::ui::TextActionItem::TextActionItem(std::string_view label) :
    ActionItem{new Gtk::MenuItem{}}
{
    cast(instance())->set_label(label.data());
}
