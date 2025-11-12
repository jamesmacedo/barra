#include "text.hpp"
#include "utils/image.hpp"
#include <complex>

Text::Text(){};

void Text::set_content(cairo_t *cr, const std::string &c) {
  cairo_text_extents_t extents;
  cairo_text_extents(cr, c.c_str(), &extents);
  width = extents.width;
  height = extents.height;
  y_bearing = extents.y_bearing;
  content = c;
}

void Text::layout(){
  if(!dirty) return;
}

void Text::draw(cairo_t *cr) {
  layout();
  cairo_move_to(cr, this->get_x(), this->get_y() - y_bearing);
  cairo_set_font_size(cr, 15);
  auto [r, g, b] = std::apply(rgb_to_cairo, color);
  cairo_set_source_rgb(cr, r, g, b);
  cairo_show_text(cr, content.c_str());
}
