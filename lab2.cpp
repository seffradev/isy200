#include "mbed.h"
#include <chrono>

#define MAX_TIME 5000.0
#define MIN_TIME 1000.0
#define SERVO_MAX 2500
#define SERVO_MIN 500
#define PERIOD 0.020

DigitalIn joystickUp(p15);
DigitalIn joystickDown(p12);

PwmOut servo(p21);

PwmOut r(p23);
PwmOut g(p24);
PwmOut b(p25);

AnalogIn potentiometer(p19);

bool active = false;
bool keepGoing = false;
bool led = false;
double delta = 0;
double pulsewidth = SERVO_MAX;

double clamp(double value, double min, double max) {
  if (value < min)
    return min;
  else if (value > max)
    return max;
  return value;
}

int main() {
  servo.period(PERIOD);
  servo.pulsewidth_us(pulsewidth);
  r.period(PERIOD);
  r = g = b = 1;

  while (true) {
    delta = (SERVO_MAX - SERVO_MIN) /
            (MIN_TIME + (MAX_TIME - MIN_TIME) * potentiometer) *
            (active ? -1 : 1);

    if (pulsewidth < SERVO_MIN) {
      active = false;
    }

    if (keepGoing && pulsewidth > SERVO_MAX) {
      active = true;
    }

    if (joystickUp == 1) {
      keepGoing = true;
    }

    if (joystickDown == 1) {
      keepGoing = false;
    }

    pulsewidth = clamp(pulsewidth, SERVO_MIN, SERVO_MAX);
    pulsewidth += delta;
    led = active;

    r = 1 - 0.05 * (int)led;
    g = 1 - 0.05 * (int)led;
    b = 1 - 0.05 * (int)led;

    servo.pulsewidth_us(pulsewidth);
    ThisThread::sleep_for(1ms);
  }
}
