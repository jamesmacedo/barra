#include <cairo/cairo-xcb.h>
#include <cairo/cairo.h>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <stdio.h>
#include <xcb/xcb.h>
#include <xcb/xproto.h>
#include <glib.h>

#include "core/ui/layout.hpp"
#include "core/widgets/clock.hpp"

xcb_window_t root;
xcb_window_t barra;
xcb_connection_t *connection;
xcb_screen_t *screen;

cairo_surface_t *surface;
cairo_t *cr;

xcb_visualtype_t *get_visualtype(xcb_screen_t *screen) {
  xcb_depth_iterator_t depth_iter = xcb_screen_allowed_depths_iterator(screen);
  for (; depth_iter.rem; xcb_depth_next(&depth_iter)) {
    xcb_visualtype_iterator_t visual_iter =
        xcb_depth_visuals_iterator(depth_iter.data);
    for (; visual_iter.rem; xcb_visualtype_next(&visual_iter)) {
      if (screen->root_visual == visual_iter.data->visual_id) {
        return visual_iter.data;
      }
    }
  }
  return NULL;
}

void setup() {
  connection = xcb_connect(NULL, NULL);
  if (xcb_connection_has_error(connection)) {
    std::cout << "Error trying to connect to X server" << std::endl;
    exit(EXIT_FAILURE);
  }

  screen = xcb_setup_roots_iterator(xcb_get_setup(connection)).data;
  root = screen->root;

  barra = xcb_generate_id(connection);

  xcb_create_window(
      connection, XCB_COPY_FROM_PARENT, barra, screen->root, 0, 0,
      screen->width_in_pixels, 30, 0, XCB_WINDOW_CLASS_INPUT_OUTPUT,
      screen->root_visual, XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK,
      (uint32_t[]){screen->white_pixel,
                   XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_KEY_PRESS});

  xcb_map_window(connection, barra);
  xcb_flush(connection);

  xcb_visualtype_t *visual = get_visualtype(screen);

  surface = cairo_xcb_surface_create(connection, barra, visual,
                                     screen->width_in_pixels, 30);
  cr = cairo_create(surface);

  xcb_map_window(connection, barra);
  xcb_flush(connection);
}

void draw() {

  std::cout << "desenhando tudo" << std::endl;
  Layout layout = Layout(0, 0, screen->width_in_pixels, 30);
  // auto gear =
  

  auto clock = std::make_shared<Clock>(cr);
  layout.add(clock);
  layout.draw(cr);

  xcb_flush(connection);
}

void loop() {
  xcb_generic_event_t *event;
  while (true) {
    while ((event = xcb_poll_for_event(connection))) {
      uint8_t response_type = event->response_type & ~0x80;
      switch (response_type) {
      case XCB_KEY_PRESS:
        std::cout << "Key pressed" << std::endl;
        break;
      }
    }
    draw();
    usleep(16000);
  }
}

int main() {

  setup();
  loop();

  cairo_destroy(cr);
  cairo_surface_destroy(surface);

  return 0;
}
