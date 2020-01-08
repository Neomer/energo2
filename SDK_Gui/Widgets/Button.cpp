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

Button::Button(std::string_view label) :
        Widget(new Gtk::Button{label.data()})
{

}

Button::Button(std::string_view label, const std::function<void()> &clickedListener) :
        Widget(new Gtk::Button{label.data()})
{
    setOnClickListener(clickedListener);
}

void Button::setOnClickListener(const std::function<void()> &listener) {
    cast(instance())->signal_clicked().connect(listener);
}
