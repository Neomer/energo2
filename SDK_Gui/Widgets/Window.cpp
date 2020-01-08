//
// Created by kir on 04.01.2020.
//

#include <gtkmm.h>
inline Gtk::Window *cast(void *instance) {
    return reinterpret_cast<Gtk::Window *>(instance);
}


#include "VerticalLayout.h"
#include "Window.h"

using namespace std;
using namespace energo::ui;

Window::Window(Window *parent) :
        _instance{new Gtk::Window{}},
        _windowState{WindowState::Normal},
        _visible{true},
        _parent{parent},
        _toolbar{nullptr},
        _statusBar{nullptr},
        _actionBar{nullptr},
        _generalLayout{new VerticalLayout{}},
        _contentLayout{new VerticalLayout{}}
{
    cast(_instance)->set_position(parent != nullptr ? Gtk::WIN_POS_CENTER_ON_PARENT : Gtk::WIN_POS_CENTER_ALWAYS);
    gtk_container_add(GTK_CONTAINER(cast(_instance)->gobj()), reinterpret_cast<Gtk::Widget *>(_generalLayout->instance())->gobj());
    _generalLayout->append(
            shared_ptr<Widget>(_contentLayout),
                    Layout::SizePolicy::Expand,
                    Layout::Align::Fill);
}

Window::Window(void *instance, Window *parent) :
        _instance{instance},
        _windowState{WindowState::Normal},
        _visible{true},
        _parent{parent},
        _toolbar{nullptr},
        _statusBar{nullptr},
        _actionBar{nullptr},
        _generalLayout{new VerticalLayout{}},
        _contentLayout{new VerticalLayout{}}
{
    cast(_instance)->set_position(parent != nullptr ? Gtk::WIN_POS_CENTER_ON_PARENT : Gtk::WIN_POS_CENTER_ALWAYS);
    gtk_container_add(GTK_CONTAINER(cast(_instance)->gobj()), reinterpret_cast<Gtk::Widget *>(_generalLayout->instance())->gobj());
    _generalLayout->append(
            shared_ptr<Widget>(_contentLayout),
                    Layout::SizePolicy::Expand,
                    Layout::Align::Fill);
}

Window::~Window() {
    delete _toolbar;
    delete _statusBar;
    delete _actionBar;
}

Window &Window::setState(WindowState state) {
    switch (state) {
        case WindowState::Maximized: cast(_instance)->maximize(); break;
        case WindowState::Fullscreen: cast(_instance)->fullscreen(); break;
        case WindowState::Minimized: cast(_instance)->iconify(); break;
        case WindowState::Normal:
        {
            switch (_windowState) {
                case WindowState::Maximized: cast(_instance)->unmaximize(); break;
                case WindowState::Minimized: cast(_instance)->deiconify(); break;
                case WindowState::Fullscreen: cast(_instance)->unfullscreen(); break;
                default: break;
            }
        }
    }
    _windowState = state;
    return *this;
}


void *Window::instance() {
    return _instance;
}

void Window::show() {
    _visible = true;
    cast(_instance)->show_all();
}

void Window::hide() {
    _visible = false;
    cast(_instance)->hide();
}

Window &Window::setTitle(std::string_view title) {
    cast(_instance)->set_title(title.data());
    return *this;
}

Window &Window::addToolBar(ToolBar *toolBar) {
    delete _toolbar;
    _toolbar = toolBar;
    if (_actionBar != nullptr) {
        _generalLayout->insert(std::shared_ptr<Widget>(toolBar), 1, Layout::SizePolicy::Stretch, Layout::Align::Fill);
    } else {
        _generalLayout->append(std::shared_ptr<Widget>(toolBar), Layout::SizePolicy::Stretch, Layout::Align::Fill);
    }
    return *this;
}

Window &Window::addActionBar(ActionBar *actionBar) {
    delete _actionBar;
    _actionBar = actionBar;
    _generalLayout->prepend(std::shared_ptr<Widget>(actionBar), Layout::SizePolicy::Stretch, Layout::Align::Fill);
    return *this;
}

Window &Window::addStatusBar(StatusBar *statusBar) {
    delete _statusBar;
    _statusBar = statusBar;
    _generalLayout->append(std::shared_ptr<Widget>(statusBar), Layout::SizePolicy::Stretch, Layout::Align::Fill);
    return *this;
}

Window &Window::setLayout(Layout *layout) {
    delete _contentLayout;
    _contentLayout = layout;
    gtk_container_add(GTK_CONTAINER(cast(_instance)->gobj()), reinterpret_cast<Gtk::Widget *>(layout->instance())->gobj());
    return *this;
}

Layout *Window::contentLayout() {
    return _contentLayout;
}

Window &Window::setSize(int width, int height) {
    cast(_instance)->set_default_geometry(width, height);
    return *this;
}

void Window::close() {
    cast(_instance)->close();
}
