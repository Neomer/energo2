//
// Created by kir on 07.01.2020.
//

#include <gtkmm.h>
inline Gtk::Box *cast(void *instance) {
    return reinterpret_cast<Gtk::Box *>(instance);
}


#include <cassert>
#include "Layout.h"

using namespace std;
using namespace energo::ui;

inline Gtk::Align to_gtk_align(Layout::Align align) {
    switch (align) {
        case Layout::Align::Fill: return Gtk::ALIGN_FILL;
        case Layout::Align::Start: return Gtk::ALIGN_START;
        case Layout::Align::Center: return Gtk::ALIGN_CENTER;
        case Layout::Align::End: return Gtk::ALIGN_END;
    }
    return Gtk::ALIGN_BASELINE;
}

#define DEFAULT_PADDING     3

Layout::Layout(void *instance) :
    Widget(instance)
{

}

Layout &Layout::insert(const shared_ptr<Widget>& child, uint16_t index, SizePolicy sizePolicy, Align align) {
    assert(index < _children.size());
    cast(instance())->pack_end(
            *reinterpret_cast<Gtk::Widget *>(child->instance()),
            sizePolicy == Layout::SizePolicy::Expand,
            sizePolicy == Layout::SizePolicy::Expand,
            DEFAULT_PADDING);
    cast(instance())->reorder_child(*reinterpret_cast<Gtk::Widget *>(child->instance()), index);
    reinterpret_cast<Gtk::Widget *>(child->instance())->set_halign(to_gtk_align(align));
    
    _children.insert(_children.begin() + index, child);
    return *this;
}

Layout &Layout::append(const shared_ptr<Widget>& child, [[maybe_unused]] SizePolicy sizePolicy, [[maybe_unused]] Align align) {
    _children.push_back(child);
    cast(instance())->pack_start(
            *reinterpret_cast<Gtk::Widget *>(child->instance()),
            sizePolicy == Layout::SizePolicy::Expand,
            sizePolicy == Layout::SizePolicy::Expand,
            DEFAULT_PADDING);
    reinterpret_cast<Gtk::Widget *>(child->instance())->set_halign(to_gtk_align(align));
    return *this;
}

Layout &Layout::prepend(const shared_ptr<Widget>& child, [[maybe_unused]] SizePolicy sizePolicy, [[maybe_unused]] Align align) {
    _children.insert(_children.begin(), child);
    cast(instance())->pack_start(
            *reinterpret_cast<Gtk::Widget *>(child->instance()),
            sizePolicy == Layout::SizePolicy::Expand,
            sizePolicy == Layout::SizePolicy::Expand,
            DEFAULT_PADDING);
    cast(instance())->reorder_child(*reinterpret_cast<Gtk::Widget *>(child->instance()), 0);
    reinterpret_cast<Gtk::Widget *>(child->instance())->set_halign(to_gtk_align(align));
    return *this;
}

Layout &Layout::setPadding(uint16_t padding) {
    cast(instance())->set_margin_left(padding);
    cast(instance())->set_margin_right(padding);
    cast(instance())->set_margin_top(padding);
    cast(instance())->set_margin_bottom(padding);
    return *this;
}

Layout &Layout::setPaddingTop(uint16_t paddingTop) {
    cast(instance())->set_margin_top(paddingTop);
    return *this;
}

Layout &Layout::setPaddingBottom(uint16_t paddingBottom) {
    cast(instance())->set_margin_bottom(paddingBottom);
    return *this;
}

Layout &Layout::setPaddingLeft(uint16_t paddingLeft) {
    cast(instance())->set_margin_left(paddingLeft);
    return *this;
}

Layout &Layout::setPaddingRight(uint16_t paddingRight) {
    cast(instance())->set_margin_right(paddingRight);
    return *this;
}

#undef DEFAULT_PADDING