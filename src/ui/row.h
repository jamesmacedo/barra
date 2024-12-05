#ifndef ROW_H
#define ROW_H

#include "./drawable.h"
#include <vector>
#include <memory>

class Row {
public:
    Row(double x, double y, double spacing);
    template <typename T>
    void add(const std::shared_ptr<T>& drawable);
    void draw(cairo_t* cr) const;

private:
    double x_;
    double y_;
    double spacing_;
    std::vector<std::shared_ptr<BDrawable>> elements_;
};

#include "./row.tpp" 

#endif 

