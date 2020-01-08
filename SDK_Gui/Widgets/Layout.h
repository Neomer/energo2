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
    
    enum class Align {
        Fill,
        Start,
        Center,
        End
    };
    
    explicit Layout(void *instance);
    
    virtual Layout &insert(const std::shared_ptr<Widget>& child, uint16_t index, SizePolicy sizePolicy, Align align);
    
    virtual Layout &append(const std::shared_ptr<Widget>& child, SizePolicy sizePolicy, Align align);
    
    virtual Layout &prepend(const std::shared_ptr<Widget>& child, SizePolicy sizePolicy, Align align);
    
    [[nodiscard]] inline const std::vector<std::shared_ptr<Widget>> &children() const { return _children; }
    
    Layout &setPadding(uint16_t padding);
    Layout &setPaddingTop(uint16_t paddingTop);
    Layout &setPaddingBottom(uint16_t paddingBottom);
    Layout &setPaddingLeft(uint16_t paddingLeft);
    Layout &setPaddingRight(uint16_t paddingRight);
};

}

#endif //ENERGO_LAYOUT_H
