#include "wait.h"
#include "main.h"

/* Thin wrapper so application code does not depend on HAL directly.
   Note: HAL_Delay adds one extra tick, so the actual delay is ms to ms+1. */
void Wait(uint32_t ms)
{
    HAL_Delay(ms);
}
