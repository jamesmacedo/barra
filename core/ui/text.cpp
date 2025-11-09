#include "text.hpp"

Text::Text(cairo_t *cr, const std::string &c): content(c){
  cairo_text_extents_t extents;
  cairo_set_font_size(cr, 15);
  cairo_text_extents(cr, c.c_str(), &extents);
  width = extents.width;
  // height = extents.height + (0 - extents.y_bearing);
  height = height - y_bearing;
  y_bearing = extents.y_bearing;
  std::cout << "w: " << width << "h: " << height << '\n';
};

void Text::set_content(cairo_t *cr, const std::string &c) {
  cairo_text_extents_t extents;
  cairo_text_extents(cr, c.c_str(), &extents);
  width = extents.width;
  height = extents.height;
  y_bearing = extents.y_bearing;
  content = c;
}

void Text::draw(cairo_t *cr) {
  cairo_move_to(cr, x, y - (y_bearing/2));
  cairo_set_font_size(cr, 15);
  cairo_set_source_rgb(cr, 0, 0, 0);
  cairo_show_text(cr, content.c_str());
}
