#include "cairo.h"
#include "widget.h"
#include <vector>
#include <memory>
#include <math.h>
#include <tuple>

using namespace std;

class Container : public Widget {
protected:
  std::vector<std::shared_ptr<Widget>> children;
  double padding, spacing;

public:
  Container(std::vector<std::shared_ptr<Widget>> children, double padding = 0.0, double spacing = 4);
  Container();
  void add(std::shared_ptr<Widget> child); 
  void draw(cairo_t *cr);
  void set_color(tuple<uint8_t, uint8_t, uint8_t> c){ color = c;};

private:
  void draw_background(cairo_t* cr);
  tuple<uint8_t, uint8_t, uint8_t> color = make_tuple(255, 255, 0);

};
