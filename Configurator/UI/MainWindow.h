//
// Created by kir on 07.01.2020.
//

#ifndef ENERGO_MAINWINDOW_H
#define ENERGO_MAINWINDOW_H

#include <Widgets/Window.h>

namespace energo {

class MainWindow : public ui::Window {

public:
    class ToolBar : public ui::ToolBar {
    };
    
    class StatusBar : public ui::StatusBar {
    };
    
    class ActionBar: public ui::ActionBar {
    public:
        ActionBar();
    };
    
    MainWindow();
    
};

}

#endif //ENERGO_MAINWINDOW_H
