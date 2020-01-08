//
// Created by kir on 07.01.2020.
//

#include <gtkmm.h>
inline Gtk::MenuBar *cast(void *instance) {
    return reinterpret_cast<Gtk::MenuBar *>(instance);
}

#include "ActionBar.h"
#include "TextActionItem.h"

using namespace std;
using namespace energo::ui;

ActionBar::ActionBar() :
    Widget{new Gtk::MenuBar{}}
{

}

ActionBar::ActionBar(const models::Menu &menu) :
        Widget{new Gtk::MenuBar{}}
{
    _actions.reserve(menu.getItems().size());
    for (auto &menuItem : menu.getItems()) {
        action(menuItem->text());
    }
}

ActionBar &ActionBar::action(std::string_view label) {
    auto action = shared_ptr<ActionItem>(new TextActionItem{label});
    cast(instance())->append(*reinterpret_cast<Gtk::MenuItem *>(action->instance()));
    _actions.push_back(action);
    return *this;
}

ActionBar &ActionBar::action(ActionItem *item) {
    cast(instance())->append(*reinterpret_cast<Gtk::MenuItem *>(item->instance()));
    _actions.push_back(shared_ptr<ActionItem>{item});
    return *this;
}

void ActionBar::show() {
    Widget::show();
    cast(instance())->show_all();
}

void ActionBar::hide() {
    Widget::hide();
    cast(instance())->hide();
}
