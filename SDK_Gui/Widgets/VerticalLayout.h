//
// Created by kir on 07.01.2020.
//

#ifndef ENERGO_VERTICALLAYOUT_H
#define ENERGO_VERTICALLAYOUT_H

#include "Layout.h"

namespace energo::ui {

class EXPORTS VerticalLayout : public Layout {
public:
    VerticalLayout();
    
    Layout &insert(const std::shared_ptr<Widget> &child, uint16_t index, SizePolicy sizePolicy) override;
    
    Layout &append(const std::shared_ptr<Widget> &child, SizePolicy sizePolicy) override;
    
    Layout &prepend(const std::shared_ptr<Widget> &child, SizePolicy sizePolicy) override;
};

}

#endif //ENERGO_VERTICALLAYOUT_H
