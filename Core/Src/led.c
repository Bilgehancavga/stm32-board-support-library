#include "led.h"
#include "board.h"

/* LED index -> port/pin lookup (order must match Led_t) */
static GPIO_TypeDef * const led_port[LED_COUNT] = {
    LED_GREEN_PORT, LED_ORANGE_PORT, LED_RED_PORT, LED_BLUE_PORT
};
static const uint16_t led_pin[LED_COUNT] = {
    LED_GREEN_PIN, LED_ORANGE_PIN, LED_RED_PIN, LED_BLUE_PIN
};

void LED_Init(void)
{
    LED_CLK_ENABLE();

    GPIO_InitTypeDef cfg = {0};
    cfg.Mode  = GPIO_MODE_OUTPUT_PP;
    cfg.Pull  = GPIO_NOPULL;
    cfg.Speed = GPIO_SPEED_FREQ_LOW;

    for (int i = 0; i < LED_COUNT; i++) {
        cfg.Pin = led_pin[i];
        HAL_GPIO_Init(led_port[i], &cfg);
        HAL_GPIO_WritePin(led_port[i], led_pin[i], GPIO_PIN_RESET);   // start off
    }
}

void LED_On(Led_t led)
{
    if (led >= LED_COUNT) return;               // ignore invalid index
    HAL_GPIO_WritePin(led_port[led], led_pin[led], GPIO_PIN_SET);
}

void LED_Off(Led_t led)
{
    if (led >= LED_COUNT) return;
    HAL_GPIO_WritePin(led_port[led], led_pin[led], GPIO_PIN_RESET);
}
