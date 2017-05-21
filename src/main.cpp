#include <gtkmm.h>
#include "mainwindow.h"

int main(int argc, char **argv)
{
  auto app = Gtk::Application::create(argc, argv, "com.objectrenderer");
  MainWindow window;
  
  return app->run(window);
}
