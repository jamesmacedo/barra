#pragma once
#include "cairo.h"
#include "widget.h"
#include <math.h>
#include <memory>
#include <vector>

using namespace std;

class Container : public Widget {
protected:
  std::vector<std::shared_ptr<Widget>> children;
  double padding = 8.0, spacing = 4.0;
  tuple<uint8_t, uint8_t, uint8_t> color = make_tuple(128, 128, 128);

public:
  Container();
  Container(double padding, double spacing);

  void add(std::shared_ptr<Widget> child);
  void draw(cairo_t *cr) override;
  void layout() override;
  void set_color(tuple<uint8_t, uint8_t, uint8_t> c){ color = c;};

private:
  void draw_background(cairo_t *cr);
};
