#include "./container.hpp"
#include "core/utils/image.hpp"

int global_padding = 3;

Container::Container(std::vector<std::shared_ptr<Widget>> children,
                     double padding, double spacing)
    : Widget(padding, padding, 0, 0), children(children), spacing(spacing) {

  for (auto &child : children) {
    width += child->get_width();
  }
  // height = floor(avarage_height / children.size());
  width += (global_padding+8) * 2 + (spacing * children.size());
  height = 30 - (global_padding * 2);
  this->set_size(width, height);
}

Container::Container() {};

void Container::add(std::shared_ptr<Widget> child) {
  children.push_back(child);
}

void Container::draw_background(cairo_t *cr) {
  double r = height / 2.0;
  double x2 = x + width, y2 = y + height;
  cairo_new_sub_path(cr);
  cairo_arc(cr, x + r, y + r, r, M_PI / 2.0, M_PI * 3.0 / 2.0);
  cairo_arc(cr, x2 - r, y + r, r, M_PI * 3.0 / 2.0, M_PI / 2.0);
  cairo_close_path(cr);
}

void Container::draw(cairo_t *cr) {
  auto [r, g, b] = apply(rgb_to_cairo, color);
  cairo_set_source_rgb(cr, r, g, b);

  draw_background(cr);
  cairo_fill(cr);

  int offset_x = global_padding + 8;

  for (auto &child : children) {
    child->set_position(offset_x, y + (height - child->get_height()) / 2);
    child->draw(cr);
    offset_x = offset_x + child->get_width() + spacing;
  }
}
