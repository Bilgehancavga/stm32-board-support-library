#include "main.h"
#include "led.h"
#include "pins.h"
#include "button.h"
#include "sevenseg.h"
#include "wait.h"

int main(void)
{
    HAL_Init();
    LED_Init();
    Pins_Init();
    Buttons_Init();
    SevenSeg_Init();

    SevenSeg_On(0b01001111, 2000, 1000);   // show "3": 1 s period, on for 500 ms

    while (1)
    {
        Pin_On(PIN_1, OUT);               // PB0 high (3V)
        Wait(1);
        Pin_Off(PIN_1);                   // PB0 low (0V)
        Wait(1);                          // -> software square wave on PB0

        if (Button(BUTTON_1, 0)) {        // on button press and release
            LED_On(LED_ORANGE);            //   turn green LED on
            Wait(3000);                    //   for 300 ms
            LED_Off(LED_ORANGE);           //   then off
        }
    }
}

void Error_Handler(void)
{
    while (1) {}
}
