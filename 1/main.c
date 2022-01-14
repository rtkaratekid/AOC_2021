#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int first;
    int second;
    int third;
    int total;
}window;

void slide_window(window *w, int next_line) {
    w->first = w->second;
    w->second = w->third;
    w->third = next_line;
    w->total = w->first + w->second + w->third;
}


int main(int argc, char **argv) {

	if (argc != 2) {
		printf("Not enough arguments provided\n");
	}

	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;

	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		exit(EXIT_FAILURE);
	}

	window curr_w = {0,0,0};
	int prev_window_total = 0;
	int count = 0;

	while ((read = getline(&line, &len, fp)) != -1) {
		line[ strlen(line) - 1 ] = '\0'; // drop newline
		int line_num = atoi(line); // convert to int

		slide_window(&curr_w, line_num);

		if (curr_w.total > prev_window_total) count++; // count
		prev_window_total = curr_w.total;
	}

	// hacky way to account for starting loops edge case without reading the file from the third line
	count -= 3;
	printf("number of larger measurements is %d\n", count);

	return 0;
}
