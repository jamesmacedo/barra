#include "core/ui/widget.h"
#include "core/ui/text.hpp"
#include "core/ui/container.hpp"
#include "core/ui/icon.h"
#include <cairo/cairo.h>

class Clock : public Widget {

public:
  Clock(cairo_t *cr);
  virtual void draw(cairo_t *cr) override;
  virtual void layout() override;

private:
  std::string get_current_time();
  std::shared_ptr<Text> time_text;
  std::shared_ptr<Icon> icon;
  std::shared_ptr<Container> container;
};
