#ifndef WAIT_H
#define WAIT_H

#include <stdint.h>

void Wait(uint32_t ms);    // blocking delay in milliseconds (busy-waits, CPU does nothing else)

#endif /* WAIT_H */
