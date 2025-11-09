#include "./widget.h"
#include <string>
#include <librsvg/rsvg.h>
#include <glib.h>

class Icon: public Widget {

private:
  std::string path;
  RsvgHandle *handle;
  GError *err = NULL;

public:
  Icon(std::string p, double width, double  height) : Widget(0, 0, width, height), path(p){

    handle = rsvg_handle_new_from_file(path.c_str(), &err);  

    if(!handle){
      std::cout << "Error trying to load SVG" << "\n";
      if(err) g_error_free(err);
      exit(1);
    }
  };

  void draw(cairo_t *cr) override {
    RsvgRectangle viewport = { x, y, width, height};
    if(!rsvg_handle_render_document(handle, cr, &viewport, &err)){
      std::cout << "Error trying to render SVG" << "\n";
      if(err) g_error_free(err);
      g_object_unref(handle);
    }
  }
  
};
