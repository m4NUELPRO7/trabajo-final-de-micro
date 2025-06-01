#ifndef DEFENSA_H
#define DEFENSA_H

#include <Adafruit_ILI9341.h>

extern Adafruit_ILI9341 screen;

const uint8_t DEFENSA_WIDTH = 20;
const uint8_t DEFENSA_HEIGHT = 20;


  // Bitmap de una persona estilo pixel art (20x20)
const unsigned char personaBitmap[] = {
  0b00011000, 0b00000000, // cabeza
  0b00011000, 0b00000000,
  0b00011000, 0b00000000,
  0b00111100, 0b00000000, // cuello
  0b00111100, 0b00000000,
  0b01111110, 0b00000000, // torso
  0b01111110, 0b00000000,
  0b01111110, 0b00000000,
  0b00111100, 0b00000000, // cintura
  0b00111100, 0b00000000,
  0b01011010, 0b00000000, // piernas
  0b01011010, 0b00000000,
  0b01011010, 0b00000000,
  0b10000001, 0b00000000, // brazos
  0b10000001, 0b00000000,
  0b10000001, 0b00000000,
  0b10000001, 0b00000000,
  0b00000000, 0b00000000,
  0b00000000, 0b00000000,
  0b00000000, 0b00000000,
};


class Defensa {
private:
  int x, y;
  int velocidad;

public:
  Defensa(int startX, int startY, int vel = 60)
    : x(startX), y(startY), velocidad(vel) {}

  void dibujar() {
    screen.drawBitmap(x, y, personaBitmap, DEFENSA_WIDTH, DEFENSA_HEIGHT, ILI9341_WHITE);
  }

  void borrar() {
    screen.drawBitmap(x, y, personaBitmap, DEFENSA_WIDTH, DEFENSA_HEIGHT, ILI9341_BLACK);
  }

  void actualizar() {
    borrar();
    y += velocidad;
    dibujar();
  }

  bool fueraDePantalla() {
    return y > screen.height();
  }

  void reiniciar() {
    borrar();
    x = random(0, screen.width() - DEFENSA_WIDTH);
    y = random(-60, -20);  // reaparece fuera de pantalla
    velocidad = random(8, 16);  // velocidad aleatoria
    dibujar();
  }

  int getX() const { return x; }
  int getY() const { return y; }

};

#endif
