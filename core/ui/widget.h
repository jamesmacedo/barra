#pragma once

#include <tuple>
#include <cstdint>
#include <cairo/cairo.h>
#include <iostream>

class Widget {

protected:
  double x, y, width, height;
  std::tuple<double, double, double> rgb_to_cairo(uint8_t r, uint8_t g, uint8_t b){
    return {(double) r/255, (double) g/255, (double) b/255}; 
  } 

public:
  Widget(double x = 0, double y = 0, uint32_t width = 0, uint32_t height = 0)
      : x(x), y(y), width(width), height(height) {}

  virtual ~Widget() = default;

  virtual void draw(cairo_t *cr) = 0;
  virtual void set_position(double nx, double ny) { x = nx; y = ny; };
  virtual void set_size(double w, double h){ width = w; height = h; };

  double get_x() const { return x;};
  double get_y() const { return y;};
  double get_width() const { return width;};
  double get_height() const { return height;};

};
