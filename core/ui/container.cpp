#include "./container.hpp"
#include "core/config.h"
#include "core/utils/image.hpp"

Container::Container() {};

Container::Container(double padding, double spacing) {}

// void Container::update_topology() {
//   for (auto &child : children) {
//     width += child->get_width();
//   }
//   // height = floor(avarage_height / children.size());
//   height = BAR_HEIGHT - (PADDING * 2);
//   this->set_size(width, height);
// }

void Container::add(std::shared_ptr<Widget> child) {
  child->set_parent(this);
  children.push_back(child);
  invalidate();
}

void Container::draw_background(cairo_t *cr) {
  double r = this->get_height() / 2.0;
  double x2 = this->get_x() + this->get_width(), y2 = this->get_y() + this->get_height();
  cairo_new_sub_path(cr);
  cairo_arc(cr, this->get_x() + r, this->get_y() + r, r, M_PI / 2.0, M_PI * 3.0 / 2.0);
  cairo_arc(cr, x2 - r, this->get_y() + r, r, M_PI * 3.0 / 2.0, M_PI / 2.0);
  cairo_close_path(cr);
}

void Container::layout() {
  if (!dirty)
    return;

  double x_offset = padding;
  double max_width = 0;
  height = BAR_HEIGHT - (PADDING * 2);

  for (auto &child : children) {
    child->set_position(x_offset, (height - child->get_height()) / 2);
    child->layout();
    x_offset += child->get_width() + spacing;
    width += child->get_width();
  }

  width += padding * 3; 
  validate();
}

void Container::draw(cairo_t *cr) {
  layout();

  auto [r, g, b] = apply(rgb_to_cairo, color);
  cairo_set_source_rgb(cr, r, g, b);

  draw_background(cr);
  cairo_fill(cr);

  for (auto &child : children) {
    child->draw(cr);
  }
}
