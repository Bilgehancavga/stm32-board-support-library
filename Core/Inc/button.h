#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>

typedef enum {
    BUTTON_1 = 0,
    BUTTON_COUNT                   // number of buttons (keep last)
} Button_t;

void    Buttons_Init(void);                         // configure buttons as inputs

/* Returns 1 if the button was held for at least min_ms (minimum 20 ms,
   for debouncing) and then released; otherwise returns 0 immediately.
   Blocks while the button is held. */
uint8_t Button(Button_t button, uint32_t min_ms);

#endif /* BUTTON_H */
