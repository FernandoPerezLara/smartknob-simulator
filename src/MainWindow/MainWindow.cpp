#include "MainWindow.h"

MainWindow::MainWindow(BaseObjectType* cobject,
                       const Glib::RefPtr<Gtk::Builder>& refBuilder) :
    Gtk::ApplicationWindow(cobject),
    m_refBuilder(refBuilder) {
  auto menu_builder = Gtk::Builder::create_from_resource("/com/smartknob/simulator/MainWindow/Menu.ui");
  auto menu = menu_builder->get_object<Gio::MenuModel>("menu");

  m_gears = m_refBuilder->get_widget<Gtk::MenuButton>("gears");
  
  m_gears->set_menu_model(menu);
}

MainWindow* MainWindow::create() {
  auto refBuilder = Gtk::Builder::create_from_resource(
      "/com/smartknob/simulator/MainWindow/MainWindow.ui");
  auto window =
      Gtk::Builder::get_widget_derived<MainWindow>(refBuilder, "app_window");

  return window;
}
