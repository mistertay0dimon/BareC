#ifndef CPU_H
#define CPU_H

#include <stdint.h>
typedef struct {
	union {
        uint16_t ax;
		struct {
			uint8_t al;
			uint8_t ah;
		};
	};
	uint16_t bx;
	uint16_t cx;
	uint16_t dx;
	uint16_t cs;
	uint16_t ip;
} registers;

extern registers CPUReg;
#endif