#include "cairo.h"
#include "widget.h"
#include <math.h>
#include <memory>
#include <vector>

using namespace std;

class Container : public Widget {
protected:
  std::vector<std::shared_ptr<Widget>> children;
  double padding, spacing;
  double inner_padding = 2;

public:
  Container();
  Container(double padding = 0.0, double spacing = 4);
  void add(std::shared_ptr<Widget> child);
  void draw(cairo_t *cr);
  void update_topology();

private:
  void draw_background(cairo_t *cr);
};
