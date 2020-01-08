//
// Created by kir on 07.01.2020.
//

#include <gtkmm.h>
inline Gtk::VBox *cast(void *instance) {
    return reinterpret_cast<Gtk::VBox *>(instance);
}


#include "VerticalLayout.h"

using namespace energo::ui;

VerticalLayout::VerticalLayout() :
    Layout{new Gtk::VBox{}}
{

}
