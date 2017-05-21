#include "renderwidget.h"

RenderWidget::RenderWidget()
{
  signal_resize().connect(sigc::mem_fun(*this, &RenderWidget::resize));
  signal_render().connect(sigc::mem_fun(*this, &RenderWidget::render));  
}

RenderWidget::~RenderWidget()
{

}

void RenderWidget::resize(int width, int height)
{
  glViewport(0,0,width,height);
}  

bool RenderWidget::render(const Glib::RefPtr<Gdk::GLContext> &context)
{
  glClearColor(0.2f,0.3f,0.2f,1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}  
