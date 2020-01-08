//
// Created by kir on 08.01.2020.
//

#ifndef ENERGO_LOGINWINDOW_H
#define ENERGO_LOGINWINDOW_H

#include <Widgets/Window.h>

namespace energo {

class LoginWindow : public ui::Window {
public:
    LoginWindow();

private:
    void signInClicked();
};

}


#endif //ENERGO_LOGINWINDOW_H
