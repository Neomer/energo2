//
// Created by kir on 07.01.2020.
//

#ifndef ENERGO_LAYOUT_H
#define ENERGO_LAYOUT_H

#include <memory>
#include <vector>
#include <cinttypes>
#include "Widget.h"

namespace energo::ui {

class EXPORTS Layout : public Widget {
    std::vector<std::shared_ptr<Widget>> _children;
    
public:
    enum class SizePolicy {
        Stretch,
        Expand
    };
    
    explicit Layout(void *instance);
    
    virtual Layout &insert(const std::shared_ptr<Widget>& child, uint16_t index, SizePolicy sizePolicy);
    
    virtual Layout &append(const std::shared_ptr<Widget>& child, SizePolicy sizePolicy);
    
    virtual Layout &prepend(const std::shared_ptr<Widget>& child, SizePolicy sizePolicy);
    
    [[nodiscard]] inline const std::vector<std::shared_ptr<Widget>> &children() const { return _children; }
};

}

#endif //ENERGO_LAYOUT_H
