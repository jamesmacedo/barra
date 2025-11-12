#pragma once
#include "widget.h"
#include <cairo/cairo.h>
#include <string>

class Text : public Widget {
  std::string content;
  double x_bearing, y_bearing;
  tuple<uint8_t, uint8_t, uint8_t> color = make_tuple(0, 0, 0);

public:
  Text();

  virtual void draw(cairo_t *cr) override;
  virtual void layout() override;

  double get_y_bearing(){ return y_bearing;};
  void set_content(cairo_t *cr, const std::string &c);
  void set_color(tuple<uint8_t, uint8_t, uint8_t> c){ color = c;};
};
