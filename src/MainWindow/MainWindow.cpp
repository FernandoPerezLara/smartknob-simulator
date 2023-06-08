#include "MainWindow.h"

MainWindow::MainWindow(BaseObjectType* cobject,
                       const Glib::RefPtr<Gtk::Builder>& refBuilder) :
    Gtk::ApplicationWindow(cobject),
    m_refBuilder(refBuilder) { }

MainWindow* MainWindow::create() {
  auto refBuilder =
      Gtk::Builder::create_from_resource("/com/smartknob/simulator/window.ui");

  auto window =
      Gtk::Builder::get_widget_derived<MainWindow>(refBuilder, "app_window");

  return window;
}
