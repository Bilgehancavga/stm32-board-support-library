#ifndef LED_H
#define LED_H

typedef enum {
    LED_GREEN = 0,
    LED_ORANGE,
    LED_RED,
    LED_BLUE,
    LED_COUNT           // number of LEDs (keep last)
} Led_t;

void LED_Init(void);         // configure all LEDs as outputs, all off
void LED_On(Led_t led);      // turn the given LED on
void LED_Off(Led_t led);     // turn the given LED off

#endif /* LED_H */
