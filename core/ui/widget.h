#pragma once

#include <cairo/cairo.h>
#include <cstdint>
#include <memory>
#include <iostream>
#include <tuple>

using namespace std;

class Widget {

protected:
  double x, y, width, height;
  std::shared_ptr<Widget> child;
  Widget* parent;
  tuple<uint8_t, uint8_t, uint8_t> color = make_tuple(255, 255, 0);

public:
  Widget(tuple<uint8_t, uint8_t, uint8_t> color)
      : color(color) {}

  Widget(std::shared_ptr<Widget>child)
      : child(child) {}

  Widget(double x = 0, double y = 0, uint32_t width = 0, uint32_t height = 0)
      : x(x), y(y), width(width), height(height) {}

  virtual ~Widget() = default;

  void set_parent(Widget* p) { parent = p; }
  virtual void update_topology(){};

  virtual void draw(cairo_t *cr) = 0;
  virtual void set_color(tuple<uint8_t, uint8_t, uint8_t> c){ color = c;};
  virtual void set_position(double nx, double ny) {


    std::cout << "new x: " << nx << "new y:" << ny << '\n';
    x = nx;
    y = ny;
  };
  virtual void set_size(double w, double h) {
    width = w;
    height = h;
  };
  void set_child(std::shared_ptr<Widget> c){
    child = c;
  }

  double get_x() const { return x; };
  double get_y() const { return y; };
  double get_width() const { return width; };
  double get_height() const { return height; };
};
