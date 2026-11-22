#include "sevenseg.h"
#include "board.h"

/* Segment index -> pin lookup (bit0 = a ... bit7 = dp) */
static const uint16_t seg_pin[8] = {
    SEVENSEG_SEG_A, SEVENSEG_SEG_B, SEVENSEG_SEG_C, SEVENSEG_SEG_D,
    SEVENSEG_SEG_E, SEVENSEG_SEG_F, SEVENSEG_SEG_G, SEVENSEG_SEG_DP
};

/* Shared with the SysTick interrupt, hence volatile */
static volatile uint8_t  active    = 0;   // 1 while a pattern is being shown
static volatile uint8_t  g_pattern = 0;   // pattern to display
static volatile uint32_t period    = 0;   // blink period (ms)
static volatile uint32_t on_time   = 0;   // on-time within each period (ms)
static volatile uint32_t counter   = 0;   // current position within the period (ms)

/* Write the 8 pattern bits to the 8 segment pins */
static void write_pattern(uint8_t p)
{
    for (int i = 0; i < 8; i++) {
        uint8_t bit = (p >> i) & 1;
#if SEVENSEG_COMMON_ANODE
        bit = !bit;                              // common anode: segment is on when the pin is low
#endif
        HAL_GPIO_WritePin(SEVENSEG_PORT, seg_pin[i], bit ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }
}

void SevenSeg_Init(void)
{
    SEVENSEG_CLK_ENABLE();

    GPIO_InitTypeDef cfg = {0};
    cfg.Mode  = GPIO_MODE_OUTPUT_PP;
    cfg.Pull  = GPIO_NOPULL;
    cfg.Speed = GPIO_SPEED_FREQ_LOW;

    for (int i = 0; i < 8; i++) {
        cfg.Pin = seg_pin[i];
        HAL_GPIO_Init(SEVENSEG_PORT, &cfg);
    }
    SevenSeg_Off();
}

void SevenSeg_On(uint8_t pattern, uint32_t period_ms, uint32_t on_ms)
{
    active    = 0;          // stop the interrupt from using half-updated settings
    g_pattern = pattern;
    period    = period_ms;
    on_time   = on_ms;
    counter   = 0;
    write_pattern(pattern); // show immediately
    active    = 1;
}

void SevenSeg_Off(void)
{
    active = 0;
    write_pattern(0);
}

void SevenSeg_Tick(void)
{
    if (!active || period == 0) return;   // off, or continuously on: nothing to do

    counter++;
    if (counter >= period) counter = 0;   // start a new period

    if (counter < on_time) write_pattern(g_pattern);
    else                   write_pattern(0);
}
