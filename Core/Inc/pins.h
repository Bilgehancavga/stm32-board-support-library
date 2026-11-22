#ifndef PINS_H
#define PINS_H

#include <stdint.h>

typedef enum {
    PIN_1 = 0,
    PIN_2,
    PIN_3,
    PIN_4,
    PIN_COUNT                      // number of pins (keep last)
} Pin_t;

typedef enum {
    IN = 0,                        // input: read the pin
    OUT                            // output: drive the pin high
} PinMode_t;

void    Pins_Init(void);                      // enable the GPIO port clock
uint8_t Pin_On(Pin_t pin, PinMode_t mode);    // OUT: drive high, returns 1 | IN: returns pin level (0/1)
void    Pin_Off(Pin_t pin);                   // drive low

#endif /* PINS_H */
