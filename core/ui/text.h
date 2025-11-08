#pragma once
#include "widget.h"
#include <cairo/cairo.h>
#include <string>

class Text : public Widget {
  std::string content;

public:
  Text(cairo_t *cr, const std::string &c) : content(c) {
    cairo_text_extents_t extents;
    cairo_text_extents(cr, c.c_str(), &extents);
    width = extents.width;
    height = extents.height;
  }

  void set_content(const std::string &c) { content = c; };

  void draw(cairo_t *cr) override {
    cairo_move_to(cr, 10, 15);
    cairo_set_font_size(cr, 15);
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_show_text(cr, content.c_str());
  }
};
