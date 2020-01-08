//
// Created by kir on 07.01.2020.
//

#include <gtkmm.h>
inline Gtk::Button *cast(void *instance) {
    return reinterpret_cast<Gtk::Button *>(instance);
}

#include "Button.h"

using namespace std;
using namespace energo::ui;

Button::Button() :
    Widget(new Gtk::Button{})
{

}

Button &Button::label(string_view label) {
    cast(instance())->set_label(label.data());
}