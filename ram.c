#include "ram.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MEM_SIZE 16777216

uint8_t *memory;

int AllocateRAM() {
	// This function allocates 16MB RAM (16,777,216 bytes)

	memory = (uint8_t*)calloc(MEM_SIZE, sizeof(uint8_t));
	if (!memory) {
		printf("[ERROR] Failed to allocate RAM. System halted.\n");
		return 1;
	}

    printf("%d OK\n", MEM_SIZE);
	return 0;
}
