#include "renderwidget.h"
#include "renderer.h"

Renderer renderer = Renderer::getInstance();

RenderWidget::RenderWidget()
{
  signal_resize().connect(sigc::mem_fun(*this, &RenderWidget::resize));
  signal_render().connect(sigc::mem_fun(*this, &RenderWidget::render));
  signal_realize().connect(sigc::mem_fun(*this, &RenderWidget::realize));

}

RenderWidget::~RenderWidget()
{

}

void RenderWidget::resize(int width, int height)
{
  renderer.resize(width,height);
}  

bool RenderWidget::render(const Glib::RefPtr<Gdk::GLContext> &context)
{
  renderer.render();
  queue_render();
  return true;
}

void RenderWidget::realize()
{
  make_current();
  set_has_depth_buffer(true);
  
  Model model("../object/nanosuit.obj");
  Scene scene;
  scene.mModels.push_back(model);

  renderer.setActiveScene(scene);
  renderer.prepare();
}
  
