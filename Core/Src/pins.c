#include "pins.h"
#include "board.h"

/* Pin index -> port/pin lookup (order must match Pin_t) */
static GPIO_TypeDef * const pin_port[PIN_COUNT] = {
    PIN_1_PORT, PIN_2_PORT, PIN_3_PORT, PIN_4_PORT
};
static const uint16_t pin_bit[PIN_COUNT] = {
    PIN_1_PIN, PIN_2_PIN, PIN_3_PIN, PIN_4_PIN
};


void Pins_Init(void)
{
    PINS_CLK_ENABLE();
}


/* The pin is reconfigured on every call, so the same pin can be
   switched between input and output at runtime. */
uint8_t Pin_On(Pin_t pin, PinMode_t mode)
{
    if (pin >= PIN_COUNT) return 0;              // ignore invalid index

    GPIO_InitTypeDef cfg = {0};
    cfg.Pin   = pin_bit[pin];
    cfg.Speed = GPIO_SPEED_FREQ_LOW;

    if (mode == OUT) {
        cfg.Mode = GPIO_MODE_OUTPUT_PP;
        cfg.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(pin_port[pin], &cfg);
        HAL_GPIO_WritePin(pin_port[pin], pin_bit[pin], GPIO_PIN_SET);
        return 1;
    } else {
        cfg.Mode = GPIO_MODE_INPUT;
        cfg.Pull = GPIO_PULLDOWN;                // floating input reads 0
        HAL_GPIO_Init(pin_port[pin], &cfg);
        return (HAL_GPIO_ReadPin(pin_port[pin], pin_bit[pin]) == GPIO_PIN_SET) ? 1 : 0;
    }
}

void Pin_Off(Pin_t pin)
{
    if (pin >= PIN_COUNT) return;
    HAL_GPIO_WritePin(pin_port[pin], pin_bit[pin], GPIO_PIN_RESET);
}
