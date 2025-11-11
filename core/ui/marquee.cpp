#include "./text.hpp"
#include "widget.h"
#include <chrono>
#include <memory>

class Marquee : public Widget {
public:
  std::shared_ptr<Text> child;
  double x_scroll = 0;

  Marquee(std::shared_ptr<Text> child)
      : child(child) {}

  void update() {
    x_scroll -= 1;
    if (x_scroll < -child->get_width()) {
      x_scroll = child->get_width();
    }
  }

  void draw(cairo_t *cr) {
    // update();
    // cairo_save(cr);

    // cairo_rectangle(cr, this->get_x(), this->get_y(), child->get_width(), child->get_height());
    // cairo_clip(cr);
    //
    // cairo_move_to(cr, this->get_x() + x_scroll, this->get_y() - child->get_y_bearing());
    child->draw(cr);

    // cairo_restore(cr);
  }
};
