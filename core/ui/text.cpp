#include "text.hpp"
#include "utils/image.hpp"

Text::Text(cairo_t *cr, const std::string &c): Widget(make_tuple(0, 0, 0)), content(c){
  cairo_text_extents_t extents;
  cairo_set_font_size(cr, 15);
  cairo_text_extents(cr, c.c_str(), &extents);
  width = extents.width;
  // height = extents.height + (0 - extents.y_bearing);
  height = height - y_bearing;
  y_bearing = extents.y_bearing;
};

void Text::set_content(cairo_t *cr, const std::string &c) {
  cairo_text_extents_t extents;
  cairo_text_extents(cr, c.c_str(), &extents);
  width = extents.width;
  height = extents.height;
  y_bearing = extents.y_bearing;
  content = c;
  parent->update_topology();
}

void Text::draw(cairo_t *cr) {
  cairo_move_to(cr, x, y - y_bearing);
  cairo_set_font_size(cr, 15);
  auto [r, g, b] = std::apply(rgb_to_cairo, color);
  cairo_set_source_rgb(cr, r, g, b);
  cairo_show_text(cr, content.c_str());
}
