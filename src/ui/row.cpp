#include "./row.h"

Row::Row(double x, double y, double spacing)
    : x_(x), y_(y), spacing_(spacing) {}

void Row::draw(cairo_t* cr) const {

    // cairo_set_source_rgb(cr, 0, 1, 0);
    // cairo_paint(cr);

    double currentX = x_;
    for (const auto& element : elements_) {
        element->draw(cr, currentX, y_);
        currentX += element->getWidth() + spacing_;
    }
}

