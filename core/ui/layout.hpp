#include "cairo.h"
#include "widget.h"
#include <cstdint>
#include <vector>
#include <memory>

class Layout : public Widget {
protected:
  std::vector<std::shared_ptr<Widget>> children;
  uint32_t width, height;
  double padding = 3.0, spacing = 4.0;

public:
  Layout(double x, double y, uint32_t width, uint32_t height, double padding, double spacing);
  ~Layout();

  void add(std::shared_ptr<Widget> child);

  virtual void layout() override;
  virtual void draw(cairo_t *cr) override; 
};
