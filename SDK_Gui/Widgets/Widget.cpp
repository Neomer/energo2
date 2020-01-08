//
// Created by kir on 07.01.2020.
//

#include "Widget.h"

using namespace energo::ui;

Widget::Widget(void *instance) :
    _visible{true},
    _instance{instance}
{

}


Widget::~Widget() = default;

void Widget::hide() {
    _visible = false;
}

void Widget::show() {
    _visible = true;
}
