/*
It seems like the submarine can take a series of commands like forward 1, down 2, or up 3:

forward X increases the horizontal position by X units.
down X increases the depth by X units.
up X decreases the depth by X units.
Note that since you're on a submarine, down and up affect your depth, and so they have the opposite result of what you might expect.

The submarine seems to already have a planned course (your puzzle input). You should probably figure out where it's going. For example:

forward 5
down 5
forward 8
up 3
down 8
forward 2
Your horizontal position and depth both start at 0. The steps above would then modify them as follows:

forward 5 adds 5 to your horizontal position, a total of 5.
down 5 adds 5 to your depth, resulting in a value of 5.
forward 8 adds 8 to your horizontal position, a total of 13.
up 3 decreases your depth by 3, resulting in a value of 2.
down 8 adds 8 to your depth, resulting in a value of 10.
forward 2 adds 2 to your horizontal position, a total of 15.
After following these instructions, you would have a horizontal position of 15 and a depth of 10. (Multiplying these together produces 150.)

Calculate the horizontal position and depth you would have after following the planned course. What do you get if you multiply your final horizontal position by your final depth?
*/

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
