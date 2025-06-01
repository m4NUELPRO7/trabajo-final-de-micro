#include <Adafruit_GFX.h> 
#include <Adafruit_ILI9341.h>

#define TFT_DC   7
#define TFT_CS   6
#define TFT_MOSI 11
#define TFT_CLK  13
#define TFT_RST  10
#define TFT_MISO 12

#define BTN_LEFT  18
#define BTN_RIGHT 19
#define BOTON_DISPARO 2

#define PIN_BUZZER 8

Adafruit_ILI9341 screen = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

#include "defensa.h"
#include "jugador.h"
#include "balon.h"
#include "portero.h"

Jugador jugador(100, 280);

const int NUM_DEFENSAS = 5;
Defensa defensas[NUM_DEFENSAS] = {
  Defensa(random(0, 240), 0, random(6, 12)),
  Defensa(random(0, 240), -30, random(6, 12)),
  Defensa(random(0, 240), -60, random(6, 12)),
  Defensa(random(0, 240), -90, random(6, 12)),
  Defensa(random(0, 240), -120, random(6, 12)),
};

const int MAX_BALONES = 1;
Balon* balones[MAX_BALONES];
int numBalones = 0;

unsigned long lastUpdate = 0;
const int frameDelay = 5;

int defensasEsquivadas = 0;
bool aparecePortero = false;
Portero portero;

int melody[] = { 262, 294, 330, 349, 392, 440, 392, 349, 330, 294, 262, 294, 330, 262 };
int noteDurations[] = { 8, 8, 4, 8, 4, 4, 8, 8, 4, 4, 4, 8, 4, 2 };
int currentNote = 0;
unsigned long noteStartTime = 0;
bool musicaActiva = true;

void mostrarPantallaCarga() {
  screen.setTextColor(ILI9341_WHITE);
  screen.setTextSize(2);
  screen.setCursor(20, 50);
  screen.print("bienvenido...");
}

void pantallaPrincipal() {
  screen.fillScreen(ILI9341_BLACK);
  screen.setCursor(5, 80);
  screen.setTextColor(ILI9341_WHITE);
  screen.setTextSize(3);
  screen.print("GOAL RUNNER!");
}

void pantallaPerder() {
  musicaActiva = false;
  noTone(PIN_BUZZER);
  screen.fillScreen(ILI9341_BLACK);
  screen.setCursor(30, 80);
  screen.setTextColor(ILI9341_RED);
  screen.setTextSize(3);
  screen.print("¡GAMEOVER!");
  while (true);
}

void pantallaGanar() {
  musicaActiva = false;
  noTone(PIN_BUZZER);
  screen.fillScreen(ILI9341_BLACK);
  screen.setCursor(30, 80);
  screen.setTextColor(ILI9341_GREEN);
  screen.setTextSize(3);
  screen.print("¡YOU WIN!");
  while (true);
}

void configurarPines() {
  pinMode(BTN_LEFT, INPUT_PULLUP);
  pinMode(BTN_RIGHT, INPUT_PULLUP);
  pinMode(BOTON_DISPARO, INPUT_PULLUP);
  pinMode(PIN_BUZZER, OUTPUT);
}

void inicializarJuego() {
  jugador.dibujar();
  for (int i = 0; i < NUM_DEFENSAS; i++) {
    defensas[i].dibujar();
  }
}

bool colisiona(const Jugador& jugador, const Defensa& defensa) {
  return !(
    jugador.getX() + JUGADOR_WIDTH < defensa.getX() ||
    jugador.getX() > defensa.getX() + DEFENSA_WIDTH ||
    jugador.getY() + JUGADOR_HEIGHT < defensa.getY() ||
    jugador.getY() > defensa.getY() + DEFENSA_HEIGHT
  );
}

bool colisionBalonPortero(Balon& balon, Portero& portero) {
  int bx = balon.getX();
  int by = balon.getY();
  int px = portero.getX();
  int py = portero.getY();

  const int anchoPortero = 20;
  const int altoPortero = 20;

  return !(
    bx + 3 < px ||
    bx > px + anchoPortero ||
    by + 6 < py ||
    by > py + altoPortero
  );
}

bool balonEntraPorteria(Balon& balon) {
  int x = balon.getX();
  int y = balon.getY();
  return (x > 60 && x < 180 && y < 15);
}

bool balonFueraPantalla(Balon& balon) {
  int x = balon.getX();
  int y = balon.getY();
  return (x < 0 || x > 240 || y < 0 || y > 320);
}

void setup() {
  screen.begin();
  screen.setRotation(0);
  screen.fillScreen(ILI9341_BLACK);
  mostrarPantallaCarga();
  delay(1000);
  pantallaPrincipal();
  delay(1000);
  screen.fillScreen(ILI9341_BLACK);
  configurarPines();
  inicializarJuego();
}

void loop() {
  unsigned long now = millis();
  if (now - lastUpdate < frameDelay) return;
  lastUpdate = now;

  if (musicaActiva) {
    int duration = 1000 / noteDurations[currentNote];
    if (now - noteStartTime > duration * 1.3) {
      tone(PIN_BUZZER, melody[currentNote], duration);
      noteStartTime = now;
      currentNote = (currentNote + 1) % 8;
    }
  }

  if (digitalRead(BTN_LEFT) == LOW) jugador.moverIzquierda();
  if (digitalRead(BTN_RIGHT) == LOW) jugador.moverDerecha();

  if (digitalRead(BOTON_DISPARO) == LOW) {
    if (numBalones == 0) {
      balones[0] = new Balon(jugador.getX() + JUGADOR_WIDTH / 2 - 1, jugador.getY() - 6);
      numBalones = 1;
    }
    delay(100);
  }

  if (aparecePortero) {
    portero.borrar(screen);
    portero.mover();
    portero.dibujar(screen);
    screen.fillRect(60, 0, 120, 15, ILI9341_BLUE);
    jugador.dibujar();

    for (int i = 0; i < numBalones; i++) {
      balones[i]->mover();
      balones[i]->dibujar(screen);

      if (colisionBalonPortero(*balones[i], portero)) {
        pantallaPerder();
      } 
      else if (balonEntraPorteria(*balones[i])) {
        pantallaGanar();
      } 
      else if (balonFueraPantalla(*balones[i])) {
        pantallaPerder();
      }

      // Verificar colisión con defensas también en el estado portero
      for (int d = 0; d < NUM_DEFENSAS; d++) {
        int bx = balones[i]->getX();
        int by = balones[i]->getY();
        int dx = defensas[d].getX();
        int dy = defensas[d].getY();

        const int anchoBalon = 3;
        const int altoBalon = 6;

        if (!(bx + anchoBalon < dx || bx > dx + DEFENSA_WIDTH ||
              by + altoBalon < dy || by > dy + DEFENSA_HEIGHT)) {
          pantallaPerder();
        }
      }
    }
    return;
  }

  for (int i = 0; i < NUM_DEFENSAS; i++) {
    defensas[i].actualizar();

    if (colisiona(jugador, defensas[i])) {
      pantallaPerder();
    }

    for (int b = 0; b < numBalones; b++) {
      if (!balones[b]->estaActiva()) continue;

      int bx = balones[b]->getX();
      int by = balones[b]->getY();
      int dx = defensas[i].getX();
      int dy = defensas[i].getY();

      const int anchoBalon = 3;
      const int altoBalon = 6;

      if (!(bx + anchoBalon < dx || bx > dx + DEFENSA_WIDTH ||
            by + altoBalon < dy || by > dy + DEFENSA_HEIGHT)) {
        pantallaPerder();
      }
    }

    if (defensas[i].fueraDePantalla()) {
      defensas[i].reiniciar();
      defensasEsquivadas++;
      if (defensasEsquivadas >= 10) {
        aparecePortero = true;
        screen.fillScreen(ILI9341_BLACK);
      }
    }
  }

  for (int i = 0; i < numBalones; i++) {
    balones[i]->mover();
    if (balonFueraPantalla(*balones[i])) {
      pantallaPerder();
    }
    balones[i]->dibujar(screen);
  }

  // Eliminar balones inactivos
  for (int i = 0; i < numBalones; i++) {
    if (!balones[i]->estaActiva()) {
      delete balones[i];
      for (int j = i; j < numBalones - 1; j++) {
        balones[j] = balones[j + 1];
      }
      numBalones--;
      i--;
    }
  }
}

