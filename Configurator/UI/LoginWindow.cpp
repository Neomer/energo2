//
// Created by kir on 08.01.2020.
//

#include <memory>
#include <glibmm/i18n.h>
#include "LoginWindow.h"
#include <iostream>

#include <Widgets/Label.h>
#include <Widgets/TextBox.h>
#include <Widgets/Button.h>

using namespace std;
using namespace energo;

LoginWindow::LoginWindow() :
    Window{nullptr}
{
    setTitle(_("Вход в систему"));
    setSize(400, 150);
    
    contentLayout()->setPadding(10);
    contentLayout()->append(
            shared_ptr<ui::Widget>{new ui::Label{_("Логин:")}},
            ui::Layout::SizePolicy::Stretch,
            ui::Layout::Align::Start);
    
    contentLayout()->append(
            shared_ptr<ui::Widget>{new ui::TextBox{}},
            ui::Layout::SizePolicy::Stretch,
            ui::Layout::Align::Fill);
    
    contentLayout()->append(
            shared_ptr<ui::Widget>{new ui::Label{_("Пароль:")}},
            ui::Layout::SizePolicy::Stretch,
            ui::Layout::Align::Start);
    
    contentLayout()->append(
            shared_ptr<ui::Widget>{new ui::TextBox{}},
            ui::Layout::SizePolicy::Stretch,
            ui::Layout::Align::Fill);
    
    contentLayout()->append(
            shared_ptr<ui::Widget>{new ui::Button{_("Войти"), bind(&LoginWindow::signInClicked, this)}},
            ui::Layout::SizePolicy::Stretch,
            ui::Layout::Align::Center);
}

void LoginWindow::signInClicked() {
    close();
}
