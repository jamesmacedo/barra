#include "./layout.hpp"
#include "core/config.h"
#include "core/utils/image.hpp"

Layout::Layout(double x, double y, uint32_t width, uint32_t height, double padding = 3, double spacing = 4)
    : Widget(x, y, width, height), width(width), height(height),  padding(padding), spacing(spacing) {
    
}

Layout::~Layout() {};

void Layout::layout() {
  if (!dirty)
    return;

  int offset_x = PADDING;

  for (auto &child : children) {
    child->set_position(offset_x, (height - child->get_height())/2);
    child->layout();
    offset_x += child->get_width() + PADDING;
  }

  validate();
};

void Layout::add(std::shared_ptr<Widget> child) {
  child->set_position(padding, padding);
  child->set_parent(this);
  children.push_back(child);
  invalidate();
}

void Layout::draw(cairo_t *cr) {
  layout();

  auto [r, g, b] = rgb_to_cairo(241, 241, 241);
  cairo_set_source_rgb(cr, r, g, b);

  cairo_rectangle(cr, 0, 0, width, height);
  cairo_fill(cr);

  for (auto &child : children) {
    child->draw(cr);
  }
}
