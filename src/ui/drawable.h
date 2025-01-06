#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <cairo/cairo.h>
#include <cairo/cairo-xlib.h>

class BDrawable {
public:
    virtual void draw(cairo_t* cr, double x, double y) const = 0;
    virtual double getWidth() const = 0;
    virtual double getHeight() const = 0;
    virtual ~BDrawable() = default;
};

#endif 

