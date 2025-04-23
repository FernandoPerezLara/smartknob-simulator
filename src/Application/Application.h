#ifndef Application_h
#define Application_h

#include "../MainWindow/MainWindow.h"

#include "gtkmm.h"

class Application : public Gtk::Application {
  public:
    static Glib::RefPtr<Application> create();

  private:
    Application();

    void on_activate() override;

    MainWindow* create_window();
};

#endif
