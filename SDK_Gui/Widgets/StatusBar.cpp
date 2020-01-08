//
// Created by kir on 07.01.2020.
//

#include <gtkmm.h>

#include "StatusBar.h"

using namespace energo::ui;

StatusBar::StatusBar() :
    Widget{new Gtk::Statusbar{}}
{

}