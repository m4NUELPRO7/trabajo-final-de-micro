#ifndef BALON_H
#define BALON_H

#include <Adafruit_ILI9341.h>

extern Adafruit_ILI9341 screen;

// bala.h

class Balon {
private:
  int x, y;
  bool activo;
  int xAnterior, yAnterior; // Para guardar la posición anterior

public:
  Balon() : x(-1), y(-1), activo(false), xAnterior(-1), yAnterior(-1) {}

  Balon(int startX, int startY) : x(startX), y(startY), activo(true), xAnterior(startX), yAnterior(startY) {}




   void borrar() {
    if (activo) {
      // Borra balon de su posición anterior
      screen.fillRect(x, y, 3, 6, ILI9341_BLACK);  // Suponiendo que balon tiene un tamaño de 3x6 píxeles
      activo = false; // Desactiva balon después de borrarla
    }
  }

  void mover() {
    if (activo) {
      // Borrar la posición anterior del balon
      if (xAnterior != -1 && yAnterior != -1) {
        screen.fillRect(xAnterior, yAnterior, 3, 6, ILI9341_BLACK); // Borrar la bala anterior
      }

      // Actualizar la nueva posición
      y -= 20; // Mueve el balon 

      // Guardar la nueva posición para la siguiente vez
      xAnterior = x;
      yAnterior = y;
    }
  }

  void dibujar(Adafruit_ILI9341& screen) {
    if (activo) {
      screen.fillRect(x, y, 3, 6, ILI9341_WHITE);  // Dibuja la nueva posición de la bala
    }
  }

  void desactivar() {
    activo = false;  // Marca la bala como inactiva
  }

  bool estaActiva() const {
    return activo;  // Devuelve el estado de la bala (activa o no)
  }

  int getX() const { return x; }
  int getY() const { return y; }
  int getAncho() const { return 3; }  
  int getAlto() const { return 6; }   


  void reiniciar() {
    x = -1;
    y = -1;
    activo = false;
    xAnterior = -1;
    yAnterior = -1;
  }
};


#endif












