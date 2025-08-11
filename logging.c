#include "logging.h"
#include <stdio.h>
#include <time.h>

void Log(const char* message) {
    FILE* log_file = fopen("log.log", "a");

    if (log_file == NULL) {
        fprintf(stderr, "[ERROR] Could not open file log.log\n");
        return;
    }

    time_t current_time;
    struct tm* time_info;
    char time_string[80];

    time(&current_time);
    time_info = localtime(&current_time);
    strftime(time_string, sizeof(time_string), "[%Y-%m-%d %H:%M:%S]", time_info);
    fprintf(log_file, "%s %s\n", time_string, message);
    
    fclose(log_file);
}
