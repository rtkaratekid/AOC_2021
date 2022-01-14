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
    while ((read = getline(&line, &len, fp)) != -1) {
        line[ strlen(line) - 1 ] = '\0'; // drop newline

        //char *saveptr;
        char *saveptr, *direction, *str_value;
        int value;
        direction = strtok_r(line, " ", &saveptr); // first token
        str_value = strtok_r(NULL, " ", &saveptr); // second token
        value = atoi(str_value);

        if(strcmp(direction, "forward") == 0) {
            horizontal += value;
        } else if (strcmp(direction, "down") == 0) {
            depth += value;
        } else if (strcmp(direction, "up") == 0) {
            depth -= value;
        } else {
            printf("'%s' is not a valid direction\n", direction);
        }
    }

    printf("Depth: %d\nHorizontal: %d\nMulitplied: %d\n", depth, horizontal, depth*horizontal);

    return 0;
}
