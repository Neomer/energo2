//
// Created by kir on 04.01.2020.
//

#ifndef ENERGO_WINDOW_H
#define ENERGO_WINDOW_H

#include <global.h>
#include <memory>
#include <string_view>
#include <vector>
#include "ToolBar.h"
#include "ActionBar.h"
#include "StatusBar.h"
#include "Layout.h"

namespace energo::ui {

class EXPORTS Window {
public:
    enum class WindowState {
        Normal,
        Minimized,
        Maximized,
        Fullscreen
    };
    
private:
    void *_instance;
    WindowState _windowState{};
    bool _visible;
    Window *_parent;
    ToolBar *_toolbar;
    ActionBar *_actionBar;
    StatusBar *_statusBar;
    Layout *_generalLayout, *_contentLayout;

public:
    explicit Window(void *instance, Window *parent);
    explicit Window(Window *parent);
    virtual ~Window();
    
    Window &setState(WindowState state);
    Window &setTitle(std::string_view title);
    Window &addToolBar(ToolBar *toolBar);
    Window &addActionBar(ActionBar *actionBar);
    Window &addStatusBar(StatusBar *statusBar);
    Window &setLayout(Layout *layout);
    Window &setSize(int width, int height);
    
    Layout *contentLayout();
    
    void *instance();
    
    void show();
    void hide();
    
    void close();
};

}

#endif //ENERGO_WINDOW_H
