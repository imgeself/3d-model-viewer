#include "renderwidget.h"
#include "renderer.h"

Renderer renderer = Renderer::getInstance();
Scene scene;
Model model("../object/nanosuit.obj");
Camera camera;

RenderWidget::RenderWidget()
{
  add_events(Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_MOTION_MASK | Gdk::SCROLL_MASK);
  
  signal_resize().connect(sigc::mem_fun(*this, &RenderWidget::resize));
  signal_render().connect(sigc::mem_fun(*this, &RenderWidget::render));
  signal_realize().connect(sigc::mem_fun(*this, &RenderWidget::realize));
  signal_unrealize().connect(sigc::mem_fun(*this, &RenderWidget::unrealize));
  signal_button_press_event().connect(sigc::mem_fun(*this, &RenderWidget::onButtonClicked));
  signal_motion_notify_event().connect(sigc::mem_fun(*this, &RenderWidget::onMouseScrolled));
  signal_scroll_event().connect(sigc::mem_fun(*this, &RenderWidget::onWheelScrolled));
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
  return true;
}

void RenderWidget::realize()
{
  make_current();
  set_has_depth_buffer(true);
  
  scene.mModel = &model;
  scene.mainCamera = camera;

  renderer.setActiveScene(scene);
  renderer.prepare();
}

void RenderWidget::unrealize()
{
  renderer.cleanUp();
}  



int clickedButton;
float clickX;
float clickY;

bool RenderWidget::onButtonClicked(GdkEventButton *event)
{
  // Since motion event capture mouse motion on user click and hold button,
  // we don't have to worry about release event type.
  // Gtk already doing for use.
  if (event->type == GDK_BUTTON_PRESS) {
    clickedButton = event->button;
    clickX = event->x;
    clickY = event->y;
  }
  return false;
}  
  
bool RenderWidget::onMouseScrolled(GdkEventMotion *event)
{
  float sensitivity = 0.6f;
  // left click
  if (clickedButton == 1) {
    float xoffset = event->x - clickX;
    clickX = event->x;
    
    xoffset *= sensitivity;

    model.rotateHorizontally(xoffset);
    
  }
  // right click
  else if (clickedButton == 3) {
    float yoffset = clickY - event->y;
    float xoffset = event->x - clickX;
    clickY = event->y;
    clickX = event->x;
    
    float speed = 0.01f;
    xoffset *= sensitivity * speed;
    yoffset *= sensitivity * speed;

    if (xoffset > 0) {
      camera.move(RIGHTWARD, xoffset);
    } else if (xoffset < 0){
      camera.move(LEFTWARD, -xoffset);
    }  
    
    if (yoffset > 0) {
      camera.move(UPWARD, yoffset);
    } else if (yoffset < 0){
      camera.move(DOWNWARD, -yoffset);
    }
    
  }  
  
  // middle click
  else if (clickedButton == 2) {
    float yoffset = clickY - event->y;
    clickY = event->y;
  
    yoffset *= sensitivity;

    model.rotateVertically(yoffset);
  }

  
  queue_render();

  return false;
}  

bool RenderWidget::onWheelScrolled(GdkEventScroll *event)
{
  float speed = 0.25f;
  if (event->direction == GDK_SCROLL_UP) {
    camera.move(FORWARD, speed);
  } else if (event->direction == GDK_SCROLL_DOWN) {
    camera.move(BACKWARD, speed);
  }
 
  queue_render();
  return false;
}  
