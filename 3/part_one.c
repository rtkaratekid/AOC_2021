#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {

    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t line_len;

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    int lines = 1000; // bash cat input | wc -l
    int inputs[lines];

    // get inputs into an array
    int iterations = 0;
    while ((line_len = getline(&line, &len, fp)) > 0) {
        line[ strlen(line) - 1 ] = '\0'; // drop newline

        int line_num = (int)strtol(line, NULL, 2); // convert binary string to int

        inputs[iterations] = line_num; // add to our input array
        iterations++;
    }


    // Now we have all the input in memory and don't need to loop through the file anymore
    unsigned int gamma = 0;
    int num_columns = 12; // bash head -n 1 input | wc -c

    // for each column, starting from leftmost
    for(int i = num_columns-1; i >= 0; i--) {

        int value_count = 0;

        // for each value in inputs
        for(int j = 0; j < lines; j++) {

            // we bit shift to get the next bit column from the input values
            unsigned int shift = inputs[j] >> i;
            if(shift % 2 == 0) { // if the rightmost bit is 0
                value_count--;
            } else {
                value_count++;
            }
        }

        // we have more 0's and the gamma bit is 0
        if(value_count < 0) {
            gamma |= (0 << i);
        } else { // we have more 1's and the gamma bit is 1
            gamma |= (1 << i);
        }
    }

    // epsilon is bitwise complement of gamma;
    unsigned int epsilon = ~gamma;
    epsilon &= 0x00000FFF; // set upper 20 bits to 0, they'll be 1 by default since we only have 12 bits in our input

    printf("Gamma: %u\nEpsilon: %u\nPower: %u\n", gamma, epsilon, gamma*epsilon);

    return 0;
}
