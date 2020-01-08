//
// Created by kir on 07.01.2020.
//

#include <cassert>
#include "Layout.h"

using namespace std;
using namespace energo::ui;

Layout::Layout(void *instance) :
    Widget(instance)
{

}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
Layout &Layout::insert(const shared_ptr<Widget>& child, uint16_t index, [[maybe_unused]] SizePolicy sizePolicy) {
    assert(index < _children.size());
    _children.insert(_children.begin() + index, child);
    return *this;
}
#pragma clang diagnostic pop

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
Layout &Layout::append(const shared_ptr<Widget>& child, [[maybe_unused]] SizePolicy sizePolicy) {
    _children.push_back(child);
    return *this;
}
#pragma clang diagnostic pop

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
Layout &Layout::prepend(const shared_ptr<Widget>& child, [[maybe_unused]] SizePolicy sizePolicy) {
#pragma clang diagnostic pop
    _children.insert(_children.begin(), child);
    return *this;
}
