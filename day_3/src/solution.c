#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    printf("Hello, world!\n");

    FILE *input_file;
    char buff[255];
    char *instruction;
    const char delim[2] = ",";

    input_file = fopen("input.txt", "r");

    // @TODO: figure out how to stitch together stuff that runs over the 100 byte cut-off
    while (fgets(buff, 255, input_file)) {
        instruction = strtok(buff, delim);
        while (instruction != NULL) {
            printf("%s\n", instruction);
            instruction = strtok(NULL, delim);
        }
    }

    return EXIT_SUCCESS;
}
