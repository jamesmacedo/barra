#pragma once
#include "widget.h"
#include <cairo/cairo.h>
#include <string>

class Text : public Widget {
  std::string content;
  double x_bearing, y_bearing;

public:
  Text(cairo_t *cr, const std::string &c);

  double get_y_bearing(){ return y_bearing;};
  void set_content(cairo_t *cr, const std::string &c);
  void draw(cairo_t *cr) override;
};
