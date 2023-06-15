#include "Display.h"

Display::Display() { }

void Display::setCanvas(const Cairo::RefPtr<Cairo::Context>& cr) {
  this->canvas = cr;
}

void Display::drawPixel(int x, int y, int color) {
  int r = (color & 0xF800) >> 11;
  int g = (color & 0x07E0) >> 5;
  int b = (color & 0x001F);

  canvas->set_source_rgb(r / 31.0, g / 63.0, b / 31.0);
  canvas->rectangle(x, y, 1, 1);
  canvas->fill();
}

void Display::drawLine(int x0, int y0, int x1, int y1, int color) {
  int16_t dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
  int16_t dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
  int16_t error = dx + dy, e2;

  while (true) {
    this->drawPixel(x0, y0, color);

    if (x0 == x1 && y0 == y1) break;

    e2 = 2 * error;

    if (e2 >= dy) {
      error += dy;
      x0 += sx;
    }

    if (e2 <= dx) {
      error += dx;
      y0 += sy;
    }
  }
}

void Display::drawCircleFill(int x, int y, int radius, int color) {
  int16_t f = 1 - radius;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * radius;
  int16_t x1 = 0;
  int16_t y1 = radius;

  while (x1 < y1) {
    if (f >= 0) {
      y1--;
      ddF_y += 2;
      f += ddF_y;
    }

    x1++;
    ddF_x += 2;
    f += ddF_x;

    this->drawLine(x - x1, y + y1, x + x1, y + y1, color);
    this->drawLine(x - y1, y + x1, x + y1, y + x1, color);
    this->drawLine(x - x1, y - y1, x + x1, y - y1, color);
    this->drawLine(x - y1, y - x1, x + y1, y - x1, color);
  }

  this->drawLine(x - radius, y, x + radius, y, color);
}
