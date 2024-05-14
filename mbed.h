#include <chrono>

const int p0 = 0;
const int p1 = 1;
const int p2 = 2;
const int p3 = 3;
const int p4 = 4;
const int p5 = 5;
const int p6 = 6;
const int p7 = 7;
const int p8 = 8;
const int p9 = 9;
const int p10 = 10;
const int p11 = 11;
const int p12 = 12;
const int p13 = 13;
const int p14 = 14;
const int p15 = 15;
const int p16 = 16;
const int p17 = 17;
const int p18 = 18;
const int p19 = 19;
const int p20 = 20;
const int p21 = 21;
const int p22 = 22;
const int p23 = 23;
const int p24 = 24;
const int p25 = 25;
const int p26 = 26;
const int p27 = 27;
const int p28 = 28;
const int p29 = 29;
const int p30 = 30;

class ThisThread {
public:
  static void sleep_for(int ms);
  static void sleep_for(float s);
  static void sleep_for(double s);
  static void sleep_for(std::chrono::milliseconds ms);
  static void sleep_for(std::chrono::seconds s);
  static void sleep_for(std::chrono::duration<int> ms);
  static void sleep_for(std::chrono::duration<float> s);
  static void sleep_for(std::chrono::duration<double> s);
};

class PwmOut {
public:
  PwmOut(int pin);
  void period_ms(int period);
  void period(float period);
  void pulsewidth_us(int pulsewidth);
  void pulsewidth(float pulsewidth);
  void write(float value);

  float operator=(float value);
  float operator=(int value);
  float operator=(double value);

  friend float operator*(float lhs, PwmOut &rhs);
  friend float operator*(PwmOut &lhs, float rhs);
  friend float operator*(int lhs, PwmOut &rhs);
  friend float operator*(PwmOut &lhs, int rhs);
  friend float operator*(double lhs, PwmOut &rhs);
  friend float operator*(PwmOut &lhs, double rhs);
};

class AnalogIn {
public:
  AnalogIn(int pin);
  float read();

  friend float operator*(float lhs, AnalogIn &rhs);
  friend float operator*(AnalogIn &lhs, float rhs);
  friend float operator*(int lhs, AnalogIn &rhs);
  friend float operator*(AnalogIn &lhs, int rhs);
  friend float operator*(double lhs, AnalogIn &rhs);
  friend float operator*(AnalogIn &lhs, double rhs);
};

class DigitalIn {
public:
  DigitalIn(int pin);
  bool read();

  const friend bool operator&&(DigitalIn &lhs, bool rhs);
  friend bool operator&&(bool lhs, DigitalIn &rhs);
  friend bool operator&&(DigitalIn &lhs, DigitalIn &rhs);
  friend bool operator||(DigitalIn &lhs, bool rhs);
  friend bool operator||(bool lhs, DigitalIn &rhs);
  friend bool operator||(DigitalIn &lhs, DigitalIn &rhs);

  friend bool operator==(DigitalIn &lhs, bool rhs);
  friend bool operator==(bool lhs, DigitalIn &rhs);
  friend bool operator==(DigitalIn &lhs, DigitalIn &rhs);
  friend bool operator!=(DigitalIn &lhs, bool rhs);
  friend bool operator!=(bool lhs, DigitalIn &rhs);
  friend bool operator!=(DigitalIn &lhs, DigitalIn &rhs);

  friend bool operator!(DigitalIn &rhs);

  operator bool();
};

class DigitalOut {
public:
  DigitalOut(int pin);
  void write(bool value);

  bool operator=(bool value);
  bool operator=(int value);

  friend bool operator&&(DigitalOut &lhs, bool rhs);
  friend bool operator&&(bool lhs, DigitalOut &rhs);
  friend bool operator&&(DigitalOut &lhs, DigitalOut &rhs);
  friend bool operator||(DigitalOut &lhs, bool rhs);
  friend bool operator!(DigitalOut &lhs);
};

class BufferedSerial {
public:
  BufferedSerial(int, int, int);
  void set_format(int, int, int);
  void write(char* buffer, int size);
  char* read(char* buffer, int size);

  bool writable();
  bool readable();

  static const int None = 0;
};