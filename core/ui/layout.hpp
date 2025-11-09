#include "cairo.h"
#include "widget.h"
#include <cstdint>
#include <vector>
#include <memory>
#include "core/utils/image.hpp"

class Layout : public Widget {
protected:
  std::vector<std::shared_ptr<Widget>> children;
  uint32_t width, height;

public:

  Layout(double x = 0, double y = 0, uint32_t width = 0, uint32_t height = 0)
      : Widget(x, y, width, height), width(width), height(height) {}

  void add(std::shared_ptr<Widget> child){
    children.push_back(child);
  } 

  virtual void draw(cairo_t *cr) override {
    auto [r, g, b] = rgb_to_cairo(241, 241, 241); 
    cairo_set_source_rgb(cr, r, g, b);
    
    cairo_rectangle(cr, 0, 0, width, height);
    cairo_fill(cr);

    for (auto& child : children){
      child->draw(cr);
    }
  }
};
