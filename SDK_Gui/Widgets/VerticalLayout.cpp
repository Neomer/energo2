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

Layout &VerticalLayout::insert(const std::shared_ptr<Widget> &child, uint16_t index, SizePolicy sizePolicy) {
    Layout::insert(child, index, sizePolicy);
    cast(instance())->pack_end(*reinterpret_cast<Gtk::Widget *>(child->instance()), sizePolicy == Layout::SizePolicy::Expand, sizePolicy == Layout::SizePolicy::Expand, 0);
    cast(instance())->reorder_child(*reinterpret_cast<Gtk::Widget *>(child->instance()), index);
    return *this;
}

Layout &VerticalLayout::append(const std::shared_ptr<Widget> &child, SizePolicy sizePolicy) {
    Layout::append(child, sizePolicy);
    cast(instance())->pack_start(*reinterpret_cast<Gtk::Widget *>(child->instance()), sizePolicy == Layout::SizePolicy::Expand, sizePolicy == Layout::SizePolicy::Expand, 0);
    return *this;
}

Layout &VerticalLayout::prepend(const std::shared_ptr<Widget> &child, SizePolicy sizePolicy) {
    Layout::prepend(child, sizePolicy);
    cast(instance())->pack_start(*reinterpret_cast<Gtk::Widget *>(child->instance()), sizePolicy == Layout::SizePolicy::Expand, sizePolicy == Layout::SizePolicy::Expand, 0);
    cast(instance())->reorder_child(*reinterpret_cast<Gtk::Widget *>(child->instance()), 0);
    return *this;
}
