#ifndef BOARD_H
#define BOARD_H

#include "main.h"      // HAL names such as GPIOD, GPIO_PIN_12

/* ---- LEDs (Discovery: PD12-PD15) ---- */
#define LED_GREEN_PORT    GPIOD
#define LED_GREEN_PIN     GPIO_PIN_12

#define LED_ORANGE_PORT   GPIOD
#define LED_ORANGE_PIN    GPIO_PIN_13

#define LED_RED_PORT      GPIOD
#define LED_RED_PIN       GPIO_PIN_14

#define LED_BLUE_PORT     GPIOD
#define LED_BLUE_PIN      GPIO_PIN_15

#define LED_CLK_ENABLE()  __HAL_RCC_GPIOD_CLK_ENABLE()


/* ---- General-purpose pins (unused on Discovery) ---- */
#define PIN_1_PORT        GPIOB
#define PIN_1_PIN         GPIO_PIN_0

#define PIN_2_PORT        GPIOB
#define PIN_2_PIN         GPIO_PIN_1

#define PIN_3_PORT        GPIOB
#define PIN_3_PIN         GPIO_PIN_11

#define PIN_4_PORT        GPIOB
#define PIN_4_PIN         GPIO_PIN_12

#define PINS_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()


/* ---- Buttons (Discovery: blue user button PA0) ---- */
#define BUTTON_1_PORT        GPIOA
#define BUTTON_1_PIN         GPIO_PIN_0

#define BUTTONS_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()


/* ---- 7-segment, single digit (a..g and dp: PE8..PE15) ---- */
#define SEVENSEG_PORT          GPIOE

#define SEVENSEG_SEG_A         GPIO_PIN_8
#define SEVENSEG_SEG_B         GPIO_PIN_9
#define SEVENSEG_SEG_C         GPIO_PIN_10
#define SEVENSEG_SEG_D         GPIO_PIN_11
#define SEVENSEG_SEG_E         GPIO_PIN_12
#define SEVENSEG_SEG_F         GPIO_PIN_13
#define SEVENSEG_SEG_G         GPIO_PIN_14
#define SEVENSEG_SEG_DP        GPIO_PIN_15

#define SEVENSEG_CLK_ENABLE()  __HAL_RCC_GPIOE_CLK_ENABLE()

#define SEVENSEG_COMMON_ANODE  1   // 0 = common cathode (segment on at 1), 1 = common anode (segment on at 0)

#endif /* BOARD_H */
