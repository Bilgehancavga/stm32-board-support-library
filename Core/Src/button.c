#include "button.h"
#include "board.h"

/* Button index -> port/pin lookup (order must match Button_t) */
static GPIO_TypeDef * const button_port[BUTTON_COUNT] = { BUTTON_1_PORT };
static const uint16_t       button_pin[BUTTON_COUNT]  = { BUTTON_1_PIN  };

#define BUTTON_MIN_MS  20      // shortest valid press, filters contact bounce

void Buttons_Init(void)
{
    BUTTONS_CLK_ENABLE();

    GPIO_InitTypeDef cfg = {0};
    cfg.Mode = GPIO_MODE_INPUT;
    cfg.Pull = GPIO_NOPULL;                     // Discovery has an external pull-down on PA0

    for (int i = 0; i < BUTTON_COUNT; i++) {
        cfg.Pin = button_pin[i];
        HAL_GPIO_Init(button_port[i], &cfg);
    }
}

uint8_t Button(Button_t button, uint32_t min_ms)
{
    if (button >= BUTTON_COUNT) return 0;                        // ignore invalid index
    if (min_ms < BUTTON_MIN_MS) min_ms = BUTTON_MIN_MS;

    GPIO_TypeDef *port = button_port[button];
    uint16_t      pin  = button_pin[button];

    if (HAL_GPIO_ReadPin(port, pin) == GPIO_PIN_RESET)           // not pressed
        return 0;

    uint32_t start = HAL_GetTick();                              // press start time (ms)

    while (HAL_GPIO_ReadPin(port, pin) == GPIO_PIN_SET) {
        if (HAL_GetTick() - start >= min_ms) {                   // held long enough
            while (HAL_GPIO_ReadPin(port, pin) == GPIO_PIN_SET) {}   // wait for release
            HAL_Delay(BUTTON_MIN_MS);                            // skip release bounce
            return 1;
        }
    }
    return 0;                                                    // released too early
}
