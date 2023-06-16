#include "MainWindow.h"

MainWindow::MainWindow(BaseObjectType* cobject,
                       const Glib::RefPtr<Gtk::Builder>& refBuilder) :
    Gtk::ApplicationWindow(cobject),
    m_refBuilder(refBuilder) {
  auto css_provider = Gtk::CssProvider::create();
  css_provider->load_from_resource(
      "/com/smartknob/simulator/MainWindow/style.css");
  auto display = Gdk::Display::get_default();
  Gtk::StyleContext::add_provider_for_display(
      display, css_provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  auto menu = m_refBuilder->get_object<Gio::MenuModel>("menu");
  m_gears = m_refBuilder->get_widget<Gtk::MenuButton>("gears");
  m_gears->set_menu_model(menu);

  m_drawingArea = m_refBuilder->get_widget<Gtk::DrawingArea>("drawing_area");
  m_drawingArea->set_content_width(DISPLAY_SIZE);
  m_drawingArea->set_content_height(DISPLAY_SIZE);
  m_drawingArea->set_draw_func(sigc::mem_fun(*this, &MainWindow::on_draw));

  // m_label = m_refBuilder->get_widget<Gtk::Label>("label");
  m_lbl_name = m_refBuilder->get_widget<Gtk::Label>("lbl-name");
  m_lbl_pointer_minimum =
      m_refBuilder->get_widget<Gtk::Label>("lbl-pointer-minimum");
  m_lbl_pointer_maximum =
      m_refBuilder->get_widget<Gtk::Label>("lbl-pointer-maximum");
  m_lbl_pointer_default =
      m_refBuilder->get_widget<Gtk::Label>("lbl-pointer-default");
  m_lbl_pointer_steps_value =
      m_refBuilder->get_widget<Gtk::Label>("lbl-pointer-steps-value");
  m_lbl_pointer_steps_size =
      m_refBuilder->get_widget<Gtk::Label>("lbl-pointer-steps-size");
  m_lbl_pointer_steps_response =
      m_refBuilder->get_widget<Gtk::Label>("lbl-pointer-steps-response");
  m_lbl_icon_type = m_refBuilder->get_widget<Gtk::Label>("lbl-icon-type");
  m_lbl_icon_color_on =
      m_refBuilder->get_widget<Gtk::Label>("lbl-icon-color-on");
  m_lbl_icon_color_off =
      m_refBuilder->get_widget<Gtk::Label>("lbl-icon-color-off");
  m_lbl_signal_move = m_refBuilder->get_widget<Gtk::Label>("lbl-signal-move");
  m_lbl_signal_hold = m_refBuilder->get_widget<Gtk::Label>("lbl-signal-hold");

  m_slider = m_refBuilder->get_widget<Gtk::Scale>("slider");
  m_slider->signal_value_changed().connect(
      sigc::mem_fun(*this, &MainWindow::on_slider_value_changed));
  // update_steps_label();

  update_labels();
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

  display.setCanvas(cr);

  cr->set_source_rgb(0, 0, 0);
  cr->arc(DISPLAY_SIZE / 2, DISPLAY_SIZE / 2, DISPLAY_SIZE / 2, 0, 2 * M_PI);
  cr->fill();

  int angle = m_slider->get_value() * 360 / 100;
  int radius = (DISPLAY_SIZE / 2) - POINTER_SIZE - POINTER_MARGIN;

  int x = DISPLAY_SIZE / 2 + radius * cos((angle - 45) * M_PI / 90);
  int y = DISPLAY_SIZE / 2 + radius * sin((angle - 45) * M_PI / 90);

  display.drawCircleFill(x, y, POINTER_SIZE, 0xFFFF);
}

void MainWindow::on_slider_value_changed() {
  // update_steps_label();

  m_drawingArea->queue_draw();
}

void MainWindow::update_labels() {
  cards.load_file("config.yaml");

  auto card = cards.items[0];

  m_lbl_name->set_label("Name: " + card.name);
  m_lbl_pointer_minimum->set_label("Minimum value: " +
                                   std::to_string(card.pointer.minimum));
  m_lbl_pointer_maximum->set_label("Maximum value: " +
                                   std::to_string(card.pointer.maximum));
  m_lbl_pointer_default->set_label(
      "Default position: " + std::to_string(card.pointer.default_position));
  m_lbl_pointer_steps_value->set_label(
      "Value: " + std::to_string(card.pointer.steps.value));
  m_lbl_pointer_steps_size->set_label("Size of each step: " +
                                      std::to_string(card.pointer.steps.size));
  m_lbl_pointer_steps_response->set_label(
      std::string("Haptic response: ") +
      (card.pointer.steps.haptic_response ? "True" : "False"));
  m_lbl_icon_type->set_label("Type: " + card.icon.type);
  m_lbl_icon_color_off->set_label("Color when off: " + card.icon.color_off);
  m_lbl_icon_color_on->set_label("Color when on: " + card.icon.color_on);
  m_lbl_signal_move->set_label("On move: " + card.signal.move);
  m_lbl_signal_hold->set_label("On hold: " + card.signal.hold);
}

// void MainWindow::update_steps_label() {
//   int value = static_cast<int>(m_slider->get_value());

//   std::string labelText = "Name: " + std::to_string(value);

//   m_label->set_label(labelText);
// }
