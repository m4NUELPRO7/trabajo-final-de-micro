#ifndef JUGADOR_H
#define JUGADOR_H

#include <Adafruit_ILI9341.h>
#include "balon.h"

extern Adafruit_ILI9341 screen;
  // Bitmap de una persona estilo pixel art (20x20)
const unsigned char jugadorBitmap[] = {
  0b00000100, 0b00000000, //   * 
  0b00000100, 0b00000000, //   * 
  0b00000100, 0b00000000, //   * 
  0b00001110, 0b00000000, //  *** 
  0b00001110, 0b00000000, //  *** 
  0b00011110, 0b00000000, // **** 
  0b00011110, 0b00000000, // **** 
  0b00000100, 0b00000000, //   *  
  0b00000100, 0b00000000, //   *  
  0b00001110, 0b00000000, //  *** 
  0b00010100, 0b00000000, // * *  
  0b00010100, 0b00000000, // * *  
  0b00000100, 0b00000000, //   *  
  0b00001000, 0b00000000, //  *   
  0b00010000, 0b00000000, // *    
  0b00000000, 0b00000000, //      
};

  #define JUGADOR_WIDTH  16
  #define JUGADOR_HEIGHT 16
  

class Jugador {
    private:
      int x, y;
  
    public:
      Jugador(int startX, int startY) : x(startX), y(startY) {}
  
      void dibujar() {
        screen.drawBitmap(x, y, jugadorBitmap, JUGADOR_WIDTH, JUGADOR_HEIGHT, ILI9341_WHITE);
      }
  
      void borrar() {
        screen.drawBitmap(x, y, jugadorBitmap, JUGADOR_WIDTH, JUGADOR_HEIGHT, ILI9341_BLACK);
      }
  
      void moverIzquierda(int paso = 22) {
        if (x - paso >= 0) {
          borrar();
          x -= paso;
          dibujar();
        }
      }
  
      void moverDerecha(int paso = 22) {
        if (x + JUGADOR_WIDTH + paso <= screen.width()) {
          borrar();
          x += paso;
          dibujar();
        }
      }

      void reiniciar() {
        borrar();     // Borra la nave en su posición actual
        x = 100;      // Coordenada X inicial
        y = 280;      // Coordenada Y inicial
        dibujar();    // Dibuja la nave en la nueva posición
      }


      void disparar() {
        
      }
      
  
      int getX() const { return x; }
      int getY() const { return y; }
  };
  
  #endif