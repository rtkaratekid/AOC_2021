#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {

    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    int depth = 0;
    int horizontal = 0;
    int aim = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        line[ strlen(line) - 1 ] = '\0'; // drop newline

        char *saveptr, *direction, *str_value;
        int value;
        direction = strtok_r(line, " ", &saveptr); // first token
        str_value = strtok_r(NULL, " ", &saveptr); // second token
        value = atoi(str_value);


        if(strcmp(direction, "forward") == 0) {

            //forward X does two things:
            //It increases your horizontal position by X units.
            horizontal += value;

            //It increases your depth by your aim multiplied by X.
            depth += aim*value;

        } else if (strcmp(direction, "down") == 0) {

            //down X increases your aim by X units.
            aim += value;

        } else if (strcmp(direction, "up") == 0) {

            //up X decreases your aim by X units.
            aim -= value;

        } else {
            printf("'%s' is not a valid direction\n", direction);
            exit(-1);
        }
    }

    printf("Depth: %d\nHorizontal: %d\nMulitplied: %d\n", depth, horizontal, depth*horizontal);

    return 0;
}
