#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <gtkmm.h>
#include "renderwidget.h"

class MainWindow : public Gtk::Window {

public:
  MainWindow();
  ~MainWindow();

private:
  Gtk::VBox m_vbox;
  RenderWidget m_renderWidget;

};

#endif
