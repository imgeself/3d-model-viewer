#ifndef RENDER_WIDGET_H
#define RENDER_WIDGET_H

#include <gtkmm.h>
#define GLEW_STATIC
#include <GL/glew.h>

class RenderWidget : public Gtk::GLArea
{

public:
  RenderWidget();
  ~RenderWidget();

private:
  void resize(int width, int height);
  bool render(const Glib::RefPtr<Gdk::GLContext> &context);
  void realize();
};

#endif
