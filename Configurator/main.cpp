//
// Created by kir on 04.01.2020.
//

#include <gtkmm.h>
#include "UI/LoginWindow.h"

using namespace std;
using namespace energo;

int main(int argc, char **argv) {
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");
    
    LoginWindow wnd;
    wnd.show();
    
    return app->run(*reinterpret_cast<Gtk::Window*>(wnd.instance()));
}