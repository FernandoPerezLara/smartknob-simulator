#include "gtkmm.h"

#include "windows/MainWindow/MainWindow.h"

int main(int argc, char* argv[]) {
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create("com.smartknob.simulator");

  return app->make_window_and_run<MainWindow>(argc, argv);
}
