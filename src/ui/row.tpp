#ifndef ROW_TPP
#define ROW_TPP

#include "./row.h"
#include <type_traits>

template <typename T>
void Row::add(const std::shared_ptr<T>& drawable) {
    static_assert(std::is_base_of<BDrawable, T>::value, "T must derive from BDrawable");
    elements_.push_back(drawable);
}

#endif 

