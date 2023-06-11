#include "MainWindow.h"

MainWindow::MainWindow(BaseObjectType* cobject,
                       const Glib::RefPtr<Gtk::Builder>& refBuilder) :
    Gtk::ApplicationWindow(cobject),
    m_refBuilder(refBuilder) {
  auto css_provider = Gtk::CssProvider::create();
  css_provider->load_from_resource(
      "/com/smartknob/simulator/MainWindow/style.css");
  auto display = Gdk::Display::get_default();
  Gtk::StyleContext::add_provider_for_display(display, css_provider,
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);

  auto menu = m_refBuilder->get_object<Gio::MenuModel>("menu");
  m_gears = m_refBuilder->get_widget<Gtk::MenuButton>("gears");
  m_gears->set_menu_model(menu);

  m_drawingArea = m_refBuilder->get_widget<Gtk::DrawingArea>("drawing_area");
  m_drawingArea->set_draw_func(sigc::mem_fun(*this, &MainWindow::on_draw));

  m_label = m_refBuilder->get_widget<Gtk::Label>("label");

  m_slider = m_refBuilder->get_widget<Gtk::Scale>("slider");
  if (m_slider) {
    m_slider->signal_value_changed().connect(sigc::mem_fun(*this, &MainWindow::on_slider_value_changed));
  }
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
  (void) width;
  (void) height;

  double size = 120;

  cr->set_source_rgb(0.0, 0.0, 0.0);
  cr->arc(size, size, size, 0.0, 2.0 * M_PI);
  cr->fill();
}

void MainWindow::on_slider_value_changed() {
  updateStepsLabel();
}

void MainWindow::updateStepsLabel() {
  int value = static_cast<int>(m_slider->get_value());
  std::string labelText = "Steps: " + std::to_string(value);
  m_label->set_label(labelText);
}
