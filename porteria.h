#ifndef PORTERIA_H
#define PORTERIA_H

#include <Adafruit_ILI9341.h>

const uint8_t PORTERIA_WIDTH = 20;
const uint8_t PORTERIA_HEIGHT = 20;

// Bitmap simple de una portería (20x20)
const unsigned char porteriaBitmap[] = {
  0b11111111, 0b11000000,  // fila 1: marco superior
  0b10000000, 0b01000000,  // filas 2 a 18: marcos laterales
  0b10000000, 0b01000000,
  0b10000000, 0b01000000,
  0b10000000, 0b01000000,
  0b10000000, 0b01000000,
  0b10000000, 0b01000000,
  0b10000000, 0b01000000,
  0b10000000, 0b01000000,
  0b10000000, 0b01000000,
  0b10000000, 0b01000000,
  0b10000000, 0b01000000,
  0b10000000, 0b01000000,
  0b10000000, 0b01000000,
  0b10000000, 0b01000000,
  0b10000000, 0b01000000,
  0b10000000, 0b01000000,
  0b10000000, 0b01000000,
  0b11111111, 0b11000000,  // fila 19: marco inferior
  0b00000000, 0b00000000   // fila 20: vacío (puede quedar o eliminarse)
};

class Porteria {
  public:
    int x, y, w, h;

    Porteria() {
      x = 60;
      y = 10;
      w = PORTERIA_WIDTH;
      h = PORTERIA_HEIGHT;
    }

    void dibujar(Adafruit_ILI9341& screen) {
      screen.drawBitmap(x, y, porteriaBitmap, w, h, ILI9341_WHITE);
    }

    void borrar(Adafruit_ILI9341& screen) {
      screen.drawBitmap(x, y, porteriaBitmap, w, h, ILI9341_BLACK);
    }
};

#endif
