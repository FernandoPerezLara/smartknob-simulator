#ifndef Display_h
#define Display_h

#include "gtkmm.h"

class Display {
  public:
    Display();

    void setCanvas(const Cairo::RefPtr<Cairo::Context>& cr);

    void drawPixel(int x, int y, int color);
    void drawLine(int x0, int y0, int x1, int y1, int color);
    void drawCircleFill(int x, int y, int radius, int color);

  private:
    Cairo::RefPtr<Cairo::Context> canvas;
};

#endif
