#include "mainwindow.h"

MainWindow::MainWindow()
{
  set_title("3D Object Renderer");
  set_default_size(800,700);  

  m_vbox.pack_start(m_renderWidget);

  add(m_vbox);

  show_all_children();
}

MainWindow::~MainWindow()
{

}
