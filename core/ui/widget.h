#pragma once

#include <cairo/cairo.h>
#include <cstdint>
#include <iostream>
#include <memory>
#include <tuple>
#include <iostream>

using namespace std;

class Widget {

protected:
  double x, y, width, height;
  bool dirty = true;

  Widget *parent = nullptr;
  std::shared_ptr<Widget> child;

public:
  Widget(){};
  Widget(double x, double y, uint32_t width, uint32_t height)
      : x(x), y(y), width(width), height(height) {}

  virtual ~Widget() = default;

  void set_parent(Widget *p) { parent = p; }

  virtual void draw(cairo_t *cr) = 0;
  virtual void layout() = 0;
  virtual void invalidate() { dirty = true; };
  virtual void validate() { dirty = false; };

  virtual void set_position(double nx, double ny) {
    x = nx;
    y = ny;
    dirty = true;
  };
  virtual void set_size(double w, double h) {
    width = w;
    height = h;
    dirty = true;
  };

  Widget *get_parent() { return parent; };
  void set_child(std::shared_ptr<Widget> c) { 
    child = c; 
  }

  double get_x() const { return parent != nullptr ? parent->get_x() + x : x; };
  double get_y() const { return parent != nullptr ? parent->get_y() + y : y; };
  double get_width() const { return width; };
  double get_height() const { return height; };
};
