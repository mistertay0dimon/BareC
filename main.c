#include "ram.h"
#include "cpu.h"
#include "logging.h"
#include <stdio.h>

void ItsAPlaceholder() {
	// If function not released, but function have a placeholder, will calls this function.
	system("pause");
}

void SetTitle() {
	system("title BareC");
	Log("Setted title 'BareC'");
}

void PrintSystemConfiguration() {
	printf("**System Configuration**\n");
	printf("CPU: BareC Virtual CPU x86\n");
	printf("RAM: %d bytes\n", MEM_SIZE);
	printf("************************\n");
}

int main(int argc, char *argv[]) {
	Log("Starting BareC Emulator...");
	Log("Version: 1.0.0");
	SetTitle();
	cpu_init(); // Initalize CPU
	AllocateRAM(); // Allocating 16MB RAM
	Log("Allocated 16,777,212 bytes RAM.");
	system("cls");
	PrintSystemConfiguration();
	
	if (argc < 2) {
		Log("Files not specifed. Halting...");
		printf("Usage: barec <filename.bin>\n");
		return 1;
	}
	
	FILE *binary_file = fopen(argv[1], "rb");
    if (binary_file == NULL) {
        Log("Could not open binary file!");
        return 1;
    }

	size_t bytes_read = fread(memory, 1, MEM_SIZE, binary_file);
    Log("Binary file loaded into memory.");
	fclose(binary_file);
	
	cpu_run();
	printf("\n");
	free(memory);
	return 0;
}
