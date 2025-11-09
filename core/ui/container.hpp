#include "cairo.h"
#include "widget.h"
#include <vector>
#include <memory>
#include <math.h>

class Container : public Widget {
protected:
  std::vector<std::shared_ptr<Widget>> children;
  double padding, spacing;

public:
  Container(std::vector<std::shared_ptr<Widget>> children, double padding = 0.0, double spacing = 4);
  Container();
  void add(std::shared_ptr<Widget> child); 
  void draw(cairo_t *cr);

private:
  void draw_background(cairo_t* cr);

};
