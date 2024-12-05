#ifndef BUTTON_H
#define BUTTON_H

#include "./drawable.h"
#include <string>

class Button : public BDrawable {
public:
    Button(double width, double height, const std::string& label);
    void draw(cairo_t* cr, double x, double y) const override;
    double getWidth() const override;
    double getHeight() const override;

private:
    double width_;
    double height_;
    std::string label_;
};

#endif 

