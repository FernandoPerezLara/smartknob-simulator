#include "MainWindow.h"

MainWindow::MainWindow(BaseObjectType* cobject,
                       const Glib::RefPtr<Gtk::Builder>& refBuilder) :
    Gtk::ApplicationWindow(cobject),
    m_refBuilder(refBuilder) {
  auto menu_builder = Gtk::Builder::create_from_resource(
      "/com/smartknob/simulator/MainWindow/Menu.ui");
  auto menu = menu_builder->get_object<Gio::MenuModel>("menu");

  m_gears = m_refBuilder->get_widget<Gtk::MenuButton>("gears");
  m_gears->set_menu_model(menu);

  m_drawingArea = m_refBuilder->get_widget<Gtk::DrawingArea>("drawing_area");
  m_drawingArea->set_draw_func(sigc::mem_fun(*this, &MainWindow::on_draw));
}

MainWindow* MainWindow::create() {
  auto refBuilder = Gtk::Builder::create_from_resource(
      "/com/smartknob/simulator/MainWindow/MainWindow.ui");
  auto window =
      Gtk::Builder::get_widget_derived<MainWindow>(refBuilder, "app_window");

  return window;
}

void MainWindow::on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width,
                         int height) {
  const double radius = 100.0;

  cr->set_source_rgb(0.0, 0.0, 0.0);
  cr->arc(width / 2, height / 2, radius, 0.0, 2.0 * M_PI);
  cr->fill();
}
