//
// Created by kir on 07.01.2020.
//

#include <glibmm/i18n.h>
#include <ViewModels/Menu.h>
#include <Widgets/TextBox.h>
#include "MainWindow.h"

using namespace std;
using namespace energo;

MainWindow::MainWindow() :
    ui::Window{nullptr}
{
    setState(ui::Window::WindowState::Maximized)
            .setTitle("Конфигуратор Energo Pro v.2")
            .addActionBar(new ActionBar{});

    contentLayout()->append(shared_ptr<ui::Widget>{new ui::TextBox{}}, ui::Layout::SizePolicy::Stretch);
    
    addStatusBar(new StatusBar{});
}

MainWindow::ActionBar::ActionBar() :
    ui::ActionBar{ui::models::Menu{
        make_shared<ui::models::MenuItem>(
                _("Файл"),
                move(vector<shared_ptr<ui::models::MenuItem>>{
                    make_shared<ui::models::MenuItem>(_("Выход"))
                })),
        make_shared<ui::models::MenuItem>(_("Вид")),
        make_shared<ui::models::MenuItem>(_("Настройки")),
        make_shared<ui::models::MenuItem>(_("Справка"))
    }}
{

}