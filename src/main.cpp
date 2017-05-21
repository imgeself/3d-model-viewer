#include <gtkmm.h>

int main(int argc, char **argv)
{
  auto app = Gtk::Application::create(argc, argv, "com.objectrenderer");
  Gtk::Window window;
  window.set_default_size(800,700);
  
  return app->run(window);
}
