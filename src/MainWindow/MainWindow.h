#ifndef MainWindow_h
#define MainWindow_h

#include "gtkmm.h"

#include "../Cards/Cards.h"
#include "../Display/Display.h"

class MainWindow : public Gtk::ApplicationWindow {
  public:
    MainWindow(BaseObjectType* cobject,
               const Glib::RefPtr<Gtk::Builder>& refBuilder);

    static MainWindow* create();

  private:
    void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width,
                 int height);
    void on_slider_value_changed();

    // void update_steps_label();
    void update_labels();

    Glib::RefPtr<Gtk::Builder> m_refBuilder;
    Gtk::MenuButton* m_gears { nullptr };
    Gtk::DrawingArea* m_drawingArea { nullptr };
    Gtk::Scale* m_slider { nullptr };
    // Gtk::Label* m_label { nullptr };
    Gtk::Label* m_lbl_name { nullptr };
    Gtk::Label* m_lbl_pointer_minimum { nullptr };
    Gtk::Label* m_lbl_pointer_maximum { nullptr };
    Gtk::Label* m_lbl_pointer_default { nullptr };
    Gtk::Label* m_lbl_pointer_steps_value { nullptr };
    Gtk::Label* m_lbl_pointer_steps_size { nullptr };
    Gtk::Label* m_lbl_pointer_steps_response { nullptr };
    Gtk::Label* m_lbl_icon_type { nullptr };
    Gtk::Label* m_lbl_icon_color_on { nullptr };
    Gtk::Label* m_lbl_icon_color_off { nullptr };
    Gtk::Label* m_lbl_signal_move { nullptr };
    Gtk::Label* m_lbl_signal_hold { nullptr };

    static constexpr double DISPLAY_SIZE = 240;
    static constexpr int POINTER_SIZE = 10 / 2;
    static constexpr int POINTER_MARGIN = 7;

    Display display;
    Cards cards;
};

#endif
