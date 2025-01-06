#include "./row.h"
#include <iostream>
#include <cmath>

using namespace std;

Row::Row(double x, double y, double spacing)
    : x_(x), y_(y), spacing_(spacing) {}

void Row::draw(cairo_t* cr) const {

    cairo_set_source_rgb(cr, 1, 1, 1);

    double width = cairo_xlib_surface_get_width(cairo_get_target(cr));
    double height = cairo_xlib_surface_get_height(cairo_get_target(cr));
    cout << width  << endl;
    cout << height  << endl;
    
    cairo_new_path(cr);
    cairo_move_to(cr, x_ + width, y_);

    cairo_arc(cr, x_ + width - RADIUS, y_ + RADIUS, RADIUS, -M_PI/2, 0);
    cairo_line_to(cr, x_ + width, y_+ height - RADIUS);

    cairo_arc(cr, x_ + width - RADIUS, y_+ height - RADIUS, RADIUS, 0, M_PI/2);
    
    cairo_line_to(cr, x_ + RADIUS, y_ + height);
    cairo_arc(cr, x_ + RADIUS, y_ + height - RADIUS, RADIUS, M_PI/2, M_PI);
    
    cairo_line_to(cr, x_, y_ + RADIUS);
    cairo_arc(cr, x_ + RADIUS, y_ + RADIUS, RADIUS, M_PI, -M_PI/2);

    cairo_close_path(cr);
    cairo_fill(cr);

    // double currentX = x_;
    // for (const auto& element : elements_) {
    //     element->draw(cr, currentX, y_);
    //     currentX += element->getWidth() + spacing_;
    // }
}

