#include "mbed.h"

DigitalOut red(p18)
DigitalOut yellow(p20)
DigitalOut green(p21)
DigitalIn button(p23)

    enum Mode {
      GoToGreen,
      GoToRed,
    };

Mode mode = GoToGreen;
bool done = false;
float duration = 2;

int main() {
  red = 1;
  yellow = 0;
  green = 0;

  while (1) {
    if (button == 1) { // Ändrar tillstånd tillsvidare.
      done = false;
      if (mode == GoToGreen) {
        mode = GoToRed;
      } else {
        mode = GoToGreen;
      }
    }
    if (done == false) { // Kollar tillstånd, köra sekvens eller ej samt vilken.
      if (mode == GoToGreen) {
        red = 1;
        yellow = 1;
        green = 0;
        wait(duration);
        red = 0;
        yellow = 0;
        green = 1;
      } else {
        red = 0;
        yellow = 1;
        green = 0;
        wait(duration);
        red = 1;
        yellow = 0;
        green = 0;
      }
      done = true;
    }
  }
}
