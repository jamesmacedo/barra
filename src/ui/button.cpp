#include "./button.h"
#include <cairo/cairo.h>

Button::Button(double width, double height, const std::string& label)
    : width_(width), height_(height), label_(label) {}

void Button::draw(cairo_t* cr, double x, double y) const {

    cairo_set_source_rgb(cr, 0.2, 0.2, 0.1);
    cairo_rectangle(cr, x, y, width_, height_);
    cairo_fill(cr);

    cairo_set_source_rgb(cr, 1, 1, 1); 
    cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 14);
    cairo_move_to(cr, x + 5, y + height_ / 2);
    cairo_show_text(cr, label_.c_str());
}

double Button::getWidth() const { return width_; }
double Button::getHeight() const { return height_; }

