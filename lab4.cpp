#include "C12832/C12832.h"
#include "mbed.h"
#include <chrono>
#include <string>

#define MAX 300
#define MIN 20
#define BASE_RATE 120
#define STEP 4
#define TONE 1.0 / 440
#define DURATION 100
#define BAUD 9600
#define DEBOUNCE_DURATION 200

void beat();
void raise_beat();
void lower_beat();
void update_lcd();
void write_rate(int rate);
void print(std::string input);

Serial pc(USBTX, USBRX, BAUD);
InterruptIn up_button(p15);
InterruptIn down_button(p12);
DigitalOut redled(p23);
DigitalOut blueled(p25);
DigitalOut greenled(p24);
AnalogIn volume(p19);
Ticker beat_rate;
Timer debouncer; // Joystick, låser på 1 rörelse
C12832 lcd(p5, p7, p6, p8, p11);
PwmOut speaker(p26);
float period;
int rate = BASE_RATE;
bool speakerToggle = false;
bool changed = false;

int main() {
  greenled = 1;
  blueled = 1;
  redled = 1;
  speaker = volume;
  speaker.period(TONE);

  period = 60.0 / (rate * 2);

  up_button.rise(&raise_beat);     // Knapp upp, puls upp
  down_button.rise(&lower_beat);   // Tvärtom
  beat_rate.attach(&beat, period); // Koppla beat-funktion till tid i perioden.

  print("\r\n");
  print("mbed metronome!\r\n");
  print("_______________\r\n");

  lcd.cls();        // Rensar skärm
  lcd.locate(0, 3); // Plats på text
  lcd.printf("Metronome");

  debouncer.start(); // Starta timern

  while (1) {
    if (changed) {
      write_rate(rate);
      update_lcd();
      changed = false;
    }

    ThisThread::sleep_for(DURATION);
  }
}

void beat() {
  beat_rate.attach(&beat, period);
  redled = !redled;                 // Lampan av och på
  speakerToggle = !speakerToggle;   // 100ms att ändra på sig
  speaker = 0.5 * speakerToggle; // Sätter volymen
}

void raise_beat() { // Öka steg med 4 i taget, går inte att hålla inne
                    // joysticken. Endast ett i taget.
  if (debouncer.read_ms() > DEBOUNCE_DURATION) {
    debouncer.reset();
    rate += STEP;
    changed = true;

    if (rate > MAX)
      rate = MAX;

    period = 60.0 / (rate * 2); // Göra om frekvens till tid.
  }
}

void lower_beat() { // Minskar steg med 4 i taget, går inte att hålla inne
                    // joysticken. Endast ett i taget.
  if (debouncer.read_ms() > DEBOUNCE_DURATION) {
    debouncer.reset();
    rate -= STEP;
    changed = true;

    if (rate < MIN)
      rate = MIN;

    period = 60.0 / (rate * 2);
  }
}

void update_lcd() { // Uppdaterar skärm
  lcd.locate(0, 15);
  lcd.printf("%d bpm", rate);
}

void write_rate(int rate) { // Gör om 120 till string
  std::string rate_str = std::to_string(rate);
  print("metronome rate is " + rate_str + "\r\n");
}

void print(std::string input) { // Seriella samband, skriver till PC/Teraterm
  if (pc.writable()) {
    pc.write(input.c_str(), input.length());
  }
}
