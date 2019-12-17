#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    printf("Hello, world!\n");
#define MAX_TRAVELLED 512000

void read_instructions(char (*instruction_sets)[512][8]) {
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



void record_path_travelled(char (*instructions)[8], int (*coordinates)[2]) {
    char *instruction;
    char operator;
    int x = 0 , y = 0, distance = 0, movement = 0, points_visited = 0;

    for (int j=0; j<512; j++) {
        instruction = instructions[j];
        operator = instruction[0];
        if (operator != '\0') {
            movement = strtol(&instruction[1], &instruction, 10);
            for (int start = points_visited; points_visited<start+movement; points_visited++) {
                switch (operator) {
                    case 'R':
                        x++;
                        break;
                    case 'L':
                        x--;
                        break;
                    case 'U':
                        y++;
                        break;
                    case 'D':
                        y--;
                        break;
                }
                coordinates[points_visited][0] = x;
                coordinates[points_visited][1] = y;
            }
        } else {
            printf("\n");
            break;
        }
    }
    coordinates[points_visited][0] = INT_MIN;
    coordinates[points_visited][1] = INT_MIN;
}


void find_intersections(int (*coordinates)[MAX_TRAVELLED][2], int (*intersections)[2]) {
    int found = 0;
    int x_1, x_2, y_1, y_2;
    for (int i=0; i<MAX_TRAVELLED; i++) {
        x_1 = coordinates[0][i][0];
        y_1 = coordinates[0][i][1];
        if ((x_1 == INT_MIN) && (y_1 == INT_MIN)) {
            break;
        }
        for (int j=0; j<MAX_TRAVELLED; j++) {
            x_2 = coordinates[1][j][0];
            y_2 = coordinates[1][j][1];
            if ((x_2 == INT_MIN) && (y_2 == INT_MIN)) {
                break;
            }
            if ((x_1 == x_2) && (y_1 == y_2)) {
                intersections[found][0] = x_1;
                intersections[found][1] = y_1;
                found++;
            }
        }
    }
    intersections[found][0] = INT_MIN;
    intersections[found][1] = INT_MIN;
}

int find_nearest_intersection_distance(int (*intersections)[2]) {
    int min_distance, distance, x_intersection, y_intersection;

    for (int i=0; i<512; i++) {
        x_intersection = intersections[i][0];
        y_intersection = intersections[i][1];
        if ((x_intersection == INT_MIN) && (y_intersection == INT_MIN)) {
            break;
        }
        distance = abs(intersections[i][0]) + abs(intersections[i][1]);
        if ((min_distance == 0) || (distance < min_distance)) {
            min_distance = distance;
        }
    }
    return min_distance;
}


int main() {
    printf("Hello, world!\n");

    char instruction_sets[2][512][8] = {0};
    int coordinates[2][MAX_TRAVELLED][2] = {0};
    int intersections[512][2];
    int min_distance;

    read_instructions(instruction_sets);

    for (int i = 0; i<2; i++) {
        record_path_travelled(instruction_sets[i], coordinates[i]);
    }

    find_intersections(coordinates, intersections);

    min_distance = find_nearest_intersection_distance(intersections);

    printf("Minimum distance: %d\n", min_distance);

    return EXIT_SUCCESS;
}
