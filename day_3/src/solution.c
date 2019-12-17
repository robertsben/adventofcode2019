#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    printf("Hello, world!\n");

    FILE *input_file;
    char buff[255];
    char *instruction_p;
    const char delim[2] = ",";
    char instruction[10];
    int should_append = 0;

    input_file = fopen("input.txt", "r");

    // @TODO: figure out how to stitch together stuff that runs over the 255 byte cut-off
    while (fgets(buff, 255, input_file)) {
        instruction_p = strtok(buff, delim);

        if ((instruction_p == buff) && (instruction_p != "\n")) {
            should_append = 1;
            printf("Yes here's a thing\n");
        }

        while (instruction_p != NULL) {
            if (should_append) {
                printf("Should be appending here\n");
                strcat(instruction, instruction_p);
                should_append = 0;
            } else {
                strcpy(instruction, instruction_p);
            }
            printf("%s\n", instruction);
            instruction_p = strtok(NULL, delim);
        }
    }

    return EXIT_SUCCESS;
}
