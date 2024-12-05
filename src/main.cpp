#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <cairo/cairo.h>
#include <cairo/cairo-xlib.h>
#include <stdio.h>
#include "ui/ui.h"

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

long unsigned int HEIGHT = 30, WIDTH = 800; 

int SPACING = 10;

const char *options[] = {
    "Menu",
    "Settings",
    "Bluetooth",
};

int text_w_size[3] = {};

int x, y;
unsigned int mask;
Window root;
Display *display;
int start_pos_x = 0;
int last_pos = 0;

void draw_taskbar(Display *display, Window window, int x, int y) {
    cairo_surface_t *surface;
    cairo_t *cr;

    surface = cairo_xlib_surface_create(display, window, DefaultVisual(display, 0), WIDTH, HEIGHT);
    cr = cairo_create(surface);

    Row row(0, 0, 10);

    for (int i = 0; i < ARRAY_SIZE(options); i++) {
        row.add(std::make_shared<Button>(100, HEIGHT, options[i]));
    }

    row.draw(cr);

    // cairo_set_source_rgb(cr, 0.1, 0.1, 0.1);
    // cairo_paint(cr);
    //
    // cairo_set_source_rgb(cr, 1, 1, 1); 
    // int rect_width = 200;
    //
    // if (y == 29) {
    //     rect_width += 100;
    //     start_pos_x = x - rect_width / 2;
    //     last_pos = x; 
    // } else {
    //     start_pos_x = last_pos - rect_width / 2;
    // }
    //
    // cairo_rectangle(cr, start_pos_x, 0, rect_width, HEIGHT);
    // cairo_fill(cr);
    //
    // cairo_set_source_rgb(cr, 1, 1, 1); 
    // cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    // cairo_set_font_size(cr, 10);
    //
    // cairo_text_extents_t extends;
    //
    // cairo_text_extents(cr, options[0], &extends);
    //
    // int center_horizontal_alignment = (HEIGHT / 2) + extends.height / 2; 
    // cairo_move_to(cr, start_pos_x, center_horizontal_alignment);

    cairo_destroy(cr);
    cairo_surface_destroy(surface);
}

int main() {
    display = XOpenDisplay(NULL);
    if (!display) {
        fprintf(stderr, "Não foi possível abrir o display X11.\n");
        return 1;
    }

    int screen = DefaultScreen(display);
    root = RootWindow(display, screen);

    WIDTH = DisplayWidth(display, screen);
    int x = 0, y = DisplayHeight(display, screen) - HEIGHT;

    Window window = XCreateSimpleWindow(display, root, x, y, WIDTH, HEIGHT, 0,
                                        BlackPixel(display, screen),
                                        BlackPixel(display, screen));

    Atom window_type = XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
    Atom dock = XInternAtom(display, "_NET_WM_WINDOW_TYPE_DOCK", False);
    XChangeProperty(display, window, window_type, XA_ATOM, 32, PropModeReplace,
                    (unsigned char *)&dock, 1);

    unsigned long strut[4] = {0, 0, 0, HEIGHT};
    XChangeProperty(display, window,
                    XInternAtom(display, "_NET_WM_STRUT", False),
                    XA_CARDINAL, 32, PropModeReplace,
                    (unsigned char *)strut, 4);

    XSelectInput(display, window, ExposureMask | KeyPressMask | PointerMotionMask);
    XMapWindow(display, window);

    DefaultVisual(display, screen);

    XEvent event;
    while (1) {
        XNextEvent(display, &event);

        switch (event.type) {
            case Expose:
            {

                    XExposeEvent *expose = &event.xexpose;
                    // fprintf(stderr, "expose %d %d %d %d\n", expose->x, expose->y, expose->width, expose->height);
                    draw_taskbar(display, expose->window, 0, 0);
            }break;
            case MotionNotify:
            {

                XMotionEvent *motion = &event.xmotion;
                printf("Mouse moved to: x=%d, y=%d\n", motion->x, motion->y);
                draw_taskbar(display, motion->window, motion->x, motion->y);
                break;
            }
        }
    }

    // cairo_destroy(cr);
    // cairo_surface_destroy(surface);
    XDestroyWindow(display, window);
    XCloseDisplay(display);

    return 0;
}

