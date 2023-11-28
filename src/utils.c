#include "util.h"

void handle_error(const char *message) {
    fprintf(stderr, "Error: %s\n", message);
    exit(EXIT_FAILURE);
}

char* read_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        handle_error("Unable to open file");
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(length + 1);
    if (buffer == NULL) {
        handle_error("Memory allocation failed");
    }

    fread(buffer, 1, length, file);
    fclose(file);
    buffer[length] = '\0';

    return buffer;
}