#ifndef MainWindow_h
#define MainWindow_h

#include "gtkmm.h"

class MainWindow : public Gtk::ApplicationWindow {
  public:
    MainWindow(BaseObjectType* cobject,
               const Glib::RefPtr<Gtk::Builder>& refBuilder);

    static MainWindow* create();

  private:
    void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width,
                 int height);

    Glib::RefPtr<Gtk::Builder> m_refBuilder;
    Gtk::MenuButton* m_gears { nullptr };
    Gtk::DrawingArea* m_drawingArea { nullptr };

    static constexpr double DISPLAY_SIZE = 240;
};

#endif
