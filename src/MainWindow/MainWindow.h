#ifndef MainWindow_h
#define MainWindow_h

#include "gtkmm.h"

class MainWindow : public Gtk::ApplicationWindow {
  public:
    MainWindow(BaseObjectType* cobject,
               const Glib::RefPtr<Gtk::Builder>& refBuilder);

    static MainWindow* create();

  private:
    Glib::RefPtr<Gtk::Builder> m_refBuilder;
};

#endif
