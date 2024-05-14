#include "mbed.h"
#include <chrono>

#define PAUSE 1ms
#define LEFT 0x0F
#define RIGHT 0xF0
#define RATE 20
#define MAX 1000000
#define BAUD 9600
#define SIZE 1

DigitalIn btnleft(p21);
DigitalIn btnright(p22);

DigitalOut ledleft(p24);
DigitalOut ledright(p25);

BufferedSerial port(p28, p27, BAUD);

char buffer[SIZE];
char transmitted;
char received;
int counter = 0;

int main()
{
    port.set_format(8, BufferedSerial::None, 1);

    while (true)
    { // Krockar inte, kör på olika sidor.
        transmitted = 0;
        if (btnleft)
        {
            transmitted |= LEFT;
        }
        if (btnright)
        {
            transmitted |= RIGHT;
        }

        if (port.writable())
        { // Kollar så att det går att skriva till vår buffer.
            buffer[0] = transmitted;
            port.write(buffer, SIZE);
        }

        if (port.readable())
        { // Kollar så det går att ta emot till vår buffer.
            port.read(buffer, SIZE);
            received = buffer[0];
        }

        if (received & LEFT)
        { // Kollar så att det finns 1:a i vänsterlampans del
            if (counter % RATE == 0)
            {
                ledleft = !ledleft;
            }
        }
        else
        {
            ledleft = 0;
        } // Trycks inte knappen ner dör lampan.
        if (received & RIGHT)
        { // Kollar så att det finns 1:a i högerlampans del
            if (counter % RATE == 0)
            {                         // Lampan blinkar
                ledright = !ledright; // Sätter till lampans andra läge.
            }
        }
        else
        {
            ledright = 0;
        }

        if (counter++ > MAX)
        { // Nollställer counter om den når förhögt värde. Buggfix.
            counter = 0;
        }

        ThisThread::sleep_for(PAUSE);
    }
}
