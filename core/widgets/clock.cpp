#include "clock.hpp"
#include "core/ui/container.hpp"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <memory>
#include <sstream>
#include <vector>

Clock::Clock(cairo_t *cr) {

  time_text = std::make_shared<Text>(cr, "00:00");
  auto container = std::make_shared<Container>(2, 2);
  container->add(std::make_shared<Icon>("/home/nemo/grafico/barra/assets/clock.svg", 15, 15));
  container->add(time_text);
  set_child(container);
};

std::string Clock::get_current_time() {
  auto now = std::chrono::system_clock::now();
  std::time_t t = std::chrono::system_clock::to_time_t(now);
  std::tm local = *std::localtime(&t);
  std::ostringstream oss;
  oss << std::put_time(&local, "%H:%M");
  return oss.str();
}

void Clock::draw(cairo_t *cr) {  
  time_text->set_content(cr, get_current_time());
  child->draw(cr);
};
