//
// Created by kir on 08.01.2020.
//

#include <gtkmm.h>
inline Gtk::Label *cast(void *instance) {
    return reinterpret_cast<Gtk::Label *>(instance);
}

#include "Label.h"

using namespace energo::ui;

Label::Label(std::string_view text) :
    Widget(new Gtk::Label{text.data()})
{
    cast(instance())->set_halign(Gtk::ALIGN_START);
}
