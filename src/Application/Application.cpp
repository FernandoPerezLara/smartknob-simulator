#include "Application.h"

Application::Application() : Gtk::Application("com.smartknob.simulator") { }

Glib::RefPtr<Application> Application::create() {
  return Glib::make_refptr_for_instance<Application>(new Application());
}

MainWindow* Application::create_window() {
  auto window = MainWindow::create();

  add_window(*window);

  return window;
}

void Application::on_activate() {
  auto window = create_window();

  window->present();
}
