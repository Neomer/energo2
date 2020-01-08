//
// Created by kir on 07.01.2020.
//

#ifndef ENERGO_WIDGET_H
#define ENERGO_WIDGET_H

#include <functional>
#include <global.h>

namespace energo::ui {

class EXPORTS Widget {
    bool _visible;
    void *_instance;
    
public:
    explicit Widget(void *instance);
    
    virtual ~Widget();
    
    virtual void show();
    
    virtual void hide();
    
    inline void *instance() { return _instance; }
    
    [[nodiscard]] inline const void *instance_const() const { return _instance; }
};

}

#endif //ENERGO_WIDGET_H
