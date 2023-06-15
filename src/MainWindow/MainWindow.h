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
    void on_slider_value_changed();

    void update_steps_label();

    Glib::RefPtr<Gtk::Builder> m_refBuilder;
    Gtk::MenuButton* m_gears { nullptr };
    Gtk::DrawingArea* m_drawingArea { nullptr };
    Gtk::Label* m_label { nullptr };
    Gtk::Scale* m_slider { nullptr };

    static constexpr double DISPLAY_SIZE = 240;
};

#endif
