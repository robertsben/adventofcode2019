#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    printf("Hello, world!\n");

    FILE *input_file;
    char buff[255];
    char *instruction_p;
    const char delim[2] = ",";
    int should_append = 0;
    int instruction_num = 0;
    int instruction_set_num = 0;
    int is_start = 1;

    input_file = fopen("input.txt", "r");

    while (fgets(buff, 255, input_file)) {
        instruction_p = strtok(buff, delim);

        // when instruction pointer and buffer are the same, means you're at the beginning of a new buffer
        if (instruction_p == buff) {
            if (is_start) {
                is_start = 0;
            } else {
                should_append = 1;
            }
        }

        // strtok will hit null when we've run out of string
        while (instruction_p != NULL) {
            // append to the previous instruction if we've just moved to a new buffer, or insert the next
            if (should_append) {
                strcat(instruction_sets[instruction_set_num][instruction_num-1], instruction_p);
                should_append = 0;
            } else {
                strcpy(instruction_sets[instruction_set_num][instruction_num], instruction_p);
                instruction_num++;
            }

            // if we hit a newline we need to strip that out of the instructions and move onto the next set
            if (strchr(instruction_p, '\n')) {
                instruction_sets[instruction_set_num][instruction_num-1][strcspn(instruction_sets[instruction_set_num][instruction_num-1], "\n")] = 0;
                instruction_set_num++;
                instruction_num = 0;
                is_start = 1;
            }
            instruction_p = strtok(NULL, delim);
        }
    }
}

int main() {
    printf("Hello, world!\n");

    char instruction_sets[2][512][8] = {0};
    char *instruction;

    read_instructions(instruction_sets);

    for (int i = 0; i<2; i++) {
        for (int j=0; j<512; j++) {
            instruction = instruction_sets[i][j];
            if (instruction[0] != '\0') {
                printf("%s,", instruction);
            } else {
                printf("\n");
                break;
            }
        }
    }

    return EXIT_SUCCESS;
}
