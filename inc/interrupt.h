#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "cpu.h"

void handle_interrupt(uint8_t interrupt_number);
void handle_int_10();

#endif // INTERRUPT_H