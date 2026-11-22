#ifndef SEVENSEG_H
#define SEVENSEG_H

#include <stdint.h>

/* Pattern bits:  bit7 bit6 bit5 bit4 bit3 bit2 bit1 bit0
                   dp    g    f    e    d    c    b    a
   Example: 0b01001111 = "3" (a, b, c, d, g) */

void SevenSeg_Init(void);                                             // configure the 8 pins as outputs, display off

/* Shows the pattern for on_ms out of every period_ms (blinking).
   period_ms = 0 keeps the pattern on continuously. */
void SevenSeg_On(uint8_t pattern, uint32_t period_ms, uint32_t on_ms);
void SevenSeg_Off(void);                                              // display fully off

void SevenSeg_Tick(void);   // called every 1 ms from the SysTick interrupt, not by the user

#endif /* SEVENSEG_H */
