//
// Created by kir on 08.01.2020.
//

#include <gtkmm.h>
inline Gtk::Entry *cast(void *instance) {
    return reinterpret_cast<Gtk::Entry *>(instance);
}

inline const Gtk::Entry *cast_const(const void *instance) {
    return reinterpret_cast<const Gtk::Entry *>(instance);
}

#include "TextBox.h"

using namespace energo::ui;

TextBox::TextBox() :
    Widget(new Gtk::Entry{})
{

}

TextBox &TextBox::setText(std::string_view text) {
    cast(instance())->set_text(text.data());
    return *this;
}

std::string_view TextBox::text() const {
    return cast_const(instance_const())->get_text().data();
}
