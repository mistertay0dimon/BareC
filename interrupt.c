#include "interrupt.h"
#include "cpu.h"
#include "logging.h"
#include <stdio.h>

extern registers CPUReg;

void handle_int_10() {
    switch ((CPUReg.ax & 0xFF00) >> 8) {
        case 0x0E: {
            uint8_t character = CPUReg.ax & 0x00FF;
            printf("%c", character);
            char log_msg[64];
            sprintf(log_msg, "INT 0x10: Display character '%c'", character);
            Log(log_msg);
            break;
        }
        default: {
            char log_msg[64];
            sprintf(log_msg, "INT 0x10: Unsupported sub-function 0x%02X in AH.", (CPUReg.ax & 0xFF00) >> 8);
            Log(log_msg);
            break;
        }
    }
}

void handle_interrupt(uint8_t interrupt_number) {
    switch (interrupt_number) {
        case 0x10: {
            handle_int_10();
            break;
        }
        default: {
            char log_msg[64];
            sprintf(log_msg, "Unknown interrupt: 0x%02X. Halting...", interrupt_number);
            Log(log_msg);
            return;
        }
    }
}
