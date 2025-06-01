#ifndef PORTERO_H
#define PORTERO_H

#include <Adafruit_ILI9341.h>
#include "balon.h"  // Asegúrate de que el archivo balon.h esté correctamente definido

// Bitmap de una persona estilo pixel art (20x20)
const unsigned char porteroBitmap[] = {
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

class Portero {
private:
  int x, y;
  int ancho, alto;
  int velocidad;
  int limiteIzq, limiteDer;

public:
  Portero() {
    x = 100;       // Posición inicial
    y = 15;        // Justo debajo de la portería
    ancho = 20;
    alto = 20;
    velocidad = 30;
    limiteIzq = 60;   // Límite izquierdo de la portería
    limiteDer = 180;  // Límite derecho de la portería
  }

  void mover() {
    x += velocidad;
    if (x <= limiteIzq || x + ancho >= limiteDer) {
      velocidad = -velocidad;
    }
  }

  void dibujar(Adafruit_ILI9341& pantalla) {
    pantalla.drawBitmap(x, y, porteroBitmap, ancho, alto, ILI9341_WHITE);
  }

  void borrar(Adafruit_ILI9341& pantalla) {
    pantalla.drawBitmap(x, y, porteroBitmap, ancho, alto, ILI9341_BLACK);
  }

  bool colisionaCon(const Balon& balon) const {
    // Asegúrate de que las dimensiones del balón coincidan con las usadas aquí
    return !(
      balon.getX() + balon.getAncho() < x ||
      balon.getX() > x + ancho ||
      balon.getY() + balon.getAlto() < y ||
      balon.getY() > y + alto
    );
  }

  int getX() const { return x; }
  int getY() const { return y; }
  int getAncho() const { return ancho; }
  int getAlto() const { return alto; }
};

#endif
