#include "cpu.h"
#include "ram.h"
#include "logging.h"
#include "interrupt.h"
#include <stdio.h>

registers CPUReg;

void cpu_init() {
	CPUReg.ax = 0;
	CPUReg.bx = 0;
	CPUReg.cx = 0;
	CPUReg.dx = 0;
	Log("CPU initialized succesfully.");
}

void cpu_run() {
	while (1) {
		uint8_t opcode = memory[ (uint32_t)CPUReg.cs * 16 + CPUReg.ip ];
		char log_msg[64];
		char error_msg[64];
		switch (opcode) {
			case 0xB8: {
			    uint8_t low_byte = memory[ (uint32_t)CPUReg.cs * 16 + CPUReg.ip + 1 ];
				uint8_t high_byte = memory[ (uint32_t)CPUReg.cs * 16 + CPUReg.ip + 2 ];
				uint16_t value = (high_byte << 8) | low_byte;
				CPUReg.ax = value;
				CPUReg.ip += 3;

				sprintf(log_msg, "Executed MOV AX, 0x%04X. Current AX: 0x%04X", value, CPUReg.ax);
				Log(log_msg);
				break;
            }

            case 0xBB: {
			    uint8_t low_byte = memory[ (uint32_t)CPUReg.cs * 16 + CPUReg.ip + 1 ];
				uint8_t high_byte = memory[ (uint32_t)CPUReg.cs * 16 + CPUReg.ip + 2 ];
				uint16_t value = (high_byte << 8) | low_byte;
				CPUReg.bx = value;
				CPUReg.ip += 3;

                sprintf(log_msg, "Executed MOV BX, 0x%04X. Current BX: 0x%04X", value, CPUReg.bx);
				Log(log_msg);
				break;
            }

            case 0xB9: {
			    uint8_t low_byte = memory[ (uint32_t)CPUReg.cs * 16 + CPUReg.ip + 1 ];
				uint8_t high_byte = memory[ (uint32_t)CPUReg.cs * 16 + CPUReg.ip + 2 ];
				uint16_t value = (high_byte << 8) | low_byte;
				CPUReg.cx = value;
				CPUReg.ip += 3;

               sprintf(log_msg, "Executed MOV CX, 0x%04X. Current CX: 0x%04X", value, CPUReg.cx);
			   Log(log_msg);
			   break;
            }

            case 0xBA: {
			    uint8_t low_byte = memory[ (uint32_t)CPUReg.cs * 16 + CPUReg.ip + 1 ];
				uint8_t high_byte = memory[ (uint32_t)CPUReg.cs * 16 + CPUReg.ip + 2 ];
				uint16_t value = (high_byte << 8) | low_byte;
				CPUReg.dx = value;
				CPUReg.ip += 3;
				
				sprintf(log_msg, "Executed MOV DX, 0x%04X. Current DX: 0x%04X", value, CPUReg.dx);
				Log(log_msg);
				break;
			}

            case 0xB0: {
				uint8_t value = memory[ (uint32_t)CPUReg.cs * 16 + CPUReg.ip + 1 ];
				CPUReg.al = value;
				CPUReg.ip += 2;
				
				sprintf(log_msg, "Executed MOV AL, 0x%04X. Current AL: 0x%04X", value, CPUReg.al);
				Log(log_msg);
				break;
			}

            case 0xB4: {
                uint8_t value = memory[ (uint32_t)CPUReg.cs * 16 + CPUReg.ip + 1 ];
				CPUReg.ah = value;
				CPUReg.ip += 2;
				
				sprintf(log_msg, "Executed MOV AH, 0x%04X. Current AH: 0x%04X", value, CPUReg.ah);
				Log(log_msg);
				break;
			}

            case 0x90: {
			    CPUReg.ip++;
				Log("Executed NOP. Nothing happened.");
				break;
            }

            case 0xCD: {
				uint8_t interrupt_number = memory[ (uint32_t)CPUReg.cs * 16 + CPUReg.ip + 1 ];
				CPUReg.ip += 2;
				handle_interrupt(interrupt_number);
				break;
			}

            case 0xF4: {
				Log("Executed HLT. Halting...");
				return;
            }

            default:
			    sprintf(error_msg, "Unknown opcode: 0x%02X. Halting.", opcode);
				Log(error_msg);
				return;
		}
	}
}
