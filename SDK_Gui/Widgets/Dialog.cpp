//
// Created by kir on 08.01.2020.
//

#include <gtkmm.h>
#include "Dialog.h"

using namespace energo::ui;

Dialog::Dialog(energo::ui::Window *parent) :
    Window(new Gtk::Dialog{}, parent)
{

}
