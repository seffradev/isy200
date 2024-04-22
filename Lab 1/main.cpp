#include "mbed.h"
#include <chrono>
#include <cstdint>

DigitalOut red(p18);
DigitalOut yellow(p20);
DigitalOut green(p21);
DigitalIn button(p23);

enum Mode {
  GoToGreen,
  GoToRed,
};

Mode mode = GoToRed;
bool done = true;
std::chrono::duration<int> duration = 2s;

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

        ThisThread::sleep_for(duration);

        red = 0;
        yellow = 0;
        green = 1;
      } else {
        red = 0;
        yellow = 1;
        green = 0;

        ThisThread::sleep_for(duration);

        red = 1;
        yellow = 0;
        green = 0;
      }

      done = true;
    }
  }
}
