#include "core/ui/text.hpp"
#include "core/ui/container.hpp"
#include "core/ui/widget.h"
#include <cairo/cairo.h>
#include <sdbus-c++/sdbus-c++.h>
#include <string>
#include <tuple>
#include <vector>

using namespace std;
using namespace sdbus;

class Media : public Widget {

public:
  Media(cairo_t *cr);
  virtual void draw(cairo_t *cr) override;

private:
  tuple<string, string> get_current_media();
  shared_ptr<Text> text;
  shared_ptr<Container> background;
  string current_title;
};
