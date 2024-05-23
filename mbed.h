#ifndef MBED_H
#define MBED_H

#include <chrono>
#include <cstdio>
#include <string>
using namespace std::chrono_literals;

typedef int PinName;

const PinName p0 = 0;
const PinName p1 = 1;
const PinName p2 = 2;
const PinName p3 = 3;
const PinName p4 = 4;
const PinName p5 = 5;
const PinName p6 = 6;
const PinName p7 = 7;
const PinName p8 = 8;
const PinName p9 = 9;
const PinName p10 = 10;
const PinName p11 = 11;
const PinName p12 = 12;
const PinName p13 = 13;
const PinName p14 = 14;
const PinName p15 = 15;
const PinName p16 = 16;
const PinName p17 = 17;
const PinName p18 = 18;
const PinName p19 = 19;
const PinName p20 = 20;
const PinName p21 = 21;
const PinName p22 = 22;
const PinName p23 = 23;
const PinName p24 = 24;
const PinName p25 = 25;
const PinName p26 = 26;
const PinName p27 = 27;
const PinName p28 = 28;
const PinName p29 = 29;
const PinName p30 = 30;
const PinName USBTX = 31;
const PinName USBRX = 32;

class ThisThread {
public:
  static void sleep_for(int);
  static void sleep_for(float);
  static void sleep_for(double);
  static void sleep_for(std::chrono::milliseconds);
  static void sleep_for(std::chrono::seconds);
  static void sleep_for(std::chrono::duration<int>);
  static void sleep_for(std::chrono::duration<float>);
  static void sleep_for(std::chrono::duration<double>);
};

class PwmOut {
public:
  PwmOut(int);
  void period_ms(int);
  void period(float);
  void pulsewidth_us(int);
  void pulsewidth(float);
  void write(float);

  float operator=(float);
  float operator=(int);
  float operator=(double);

  friend float operator*(float lhs, PwmOut);
  friend float operator*(PwmOut &lhs, float);
  friend float operator*(int lhs, PwmOut);
  friend float operator*(PwmOut &lhs, int);
  friend float operator*(double lhs, PwmOut);
  friend float operator*(PwmOut &lhs, double);

  friend bool operator&&(PwmOut &lhs, bool);
  friend bool operator&&(bool lhs, PwmOut);
  friend bool operator&&(PwmOut &lhs, PwmOut);
  friend bool operator||(PwmOut &lhs, bool);
  friend bool operator||(bool lhs, PwmOut);
  friend bool operator||(PwmOut &lhs, PwmOut);
  friend bool operator==(PwmOut &lhs, bool);
  friend bool operator==(bool lhs, PwmOut);
  friend bool operator==(PwmOut &lhs, PwmOut);
  friend bool operator!=(PwmOut &lhs, bool);
  friend bool operator!=(bool lhs, PwmOut);
  friend bool operator!=(PwmOut &lhs, PwmOut);
  friend bool operator!(PwmOut);
  operator bool();
};

class AnalogIn {
public:
  AnalogIn(int);
  float read();

  friend float operator*(float lhs, AnalogIn);
  friend float operator*(AnalogIn &lhs, float);
  friend float operator*(int lhs, AnalogIn);
  friend float operator*(AnalogIn &lhs, int);
  friend float operator*(double lhs, AnalogIn);
  friend float operator*(AnalogIn &lhs, double);
};

class DigitalIn {
public:
  DigitalIn(int);
  bool read();

  const friend bool operator&&(DigitalIn &lhs, bool);
  friend bool operator&&(bool lhs, DigitalIn);
  friend bool operator&&(DigitalIn &lhs, DigitalIn);
  friend bool operator||(DigitalIn &lhs, bool);
  friend bool operator||(bool lhs, DigitalIn);
  friend bool operator||(DigitalIn &lhs, DigitalIn);

  friend bool operator==(DigitalIn &lhs, bool);
  friend bool operator==(bool lhs, DigitalIn);
  friend bool operator==(DigitalIn &lhs, DigitalIn);
  friend bool operator!=(DigitalIn &lhs, bool);
  friend bool operator!=(bool lhs, DigitalIn);
  friend bool operator!=(DigitalIn &lhs, DigitalIn);

  friend bool operator!(DigitalIn);

  operator bool();
};

class DigitalOut {
public:
  DigitalOut(int);
  void write(bool);

  bool operator=(bool);
  bool operator=(int);

  friend bool operator&&(DigitalOut &lhs, bool);
  friend bool operator&&(bool lhs, DigitalOut);
  friend bool operator&&(DigitalOut &lhs, DigitalOut);
  friend bool operator||(DigitalOut &lhs, bool);
  friend bool operator!(DigitalOut);
};

class BufferedSerial {
public:
  BufferedSerial(int, int, int);
  void set_format(int, int, int);
  void write(char *buffer, int);
  void write(std::string, int);
  char *read(char *buffer, int);

  bool writable();
  bool readable();

  static const int None = 0;
};

class InterruptIn {
public:
  InterruptIn(int);
  void rise(void (*function)(void));
  void fall(void (*function)(void));
  void mode(int);
  void enable_irq();
  void disable_irq();
};

class Ticker {
public:
  Ticker();
  void attach(void (*function)(void), std::chrono::milliseconds);
  void detach();
};

class Stream {
public:
  void printf(const char *, ...);
  void write(char *, int);
};

class SPI {};

class Timer {
public:
  Timer();
  void start();
  void stop();
  void reset();
  std::chrono::microseconds elapsed_time();
};

#endif
