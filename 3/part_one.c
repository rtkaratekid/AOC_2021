/*
00100
11110
10110
10111
10101
01111
00111
11100
10000
11001
00010
01010

Considering only the first bit of each number, there are five 0 bits and seven 1 bits. Since the most common bit is 1, the first bit of the gamma rate is 1.
The most common second bit of the numbers in the diagnostic report is 0, so the second bit of the gamma rate is 0.
The most common value of the third, fourth, and fifth bits are 1, 1, and 0, respectively, and so the final three bits of the gamma rate are 110.

So, the gamma rate is the binary number 10110, or 22 in decimal.

The epsilon rate is calculated in a similar way; rather than use the most common bit, the least common bit from each position is used. So, the epsilon rate is 01001, or 9 in decimal. Multiplying the gamma rate (22) by the epsilon rate (9) produces the power consumption, 198.

Use the binary numbers in your diagnostic report to calculate the gamma rate and epsilon rate, then multiply them together. What is the power consumption of the submarine? (Be sure to represent your answer in decimal, not binary.)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {

    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t line_len;

    printf("opening file\n");
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    // get number of lines in file
    printf("getting number of lines\n");
    /*
    int lines = 0;
    char c;
    while((c=fgetc(fp))!=EOF) {
        if(c=='\n') lines++;
    }
    lines++; // add one more for the last line that has no \n
    */
    int lines = 1000;

    int inputs[lines];

    printf("Getting inputs\n");
    int iterations = 0;
    while ((line_len = getline(&line, &len, fp)) > 0) {
        line[ strlen(line) - 1 ] = '\0'; // drop newline

        int line_num = (int)strtol(line, NULL, 2); // convert binary string to int

        inputs[iterations] = line_num; // add to our input array
        iterations++;
    }

    // correct to this point
    

    // Now we have all the input in memory and don't need to loop through the file anymore
    printf("calculations\n");
    unsigned int gamma = 0;
    //int num_columns = line_len - 1; //assuming all rows are the same length
    int num_columns = 12;
    printf("num cols: %d\n", num_columns);
    // for each column, starting from leftmost
    for(int i = num_columns-1; i >= 0; i--) {

        int value_count = 0;
        // for each value in inputs
        for(int j = 0; j < lines; j++) {

            // we bit shift to get the next bit column from the input values
            unsigned int shift = inputs[j] >> i;
            if(shift % 2 == 0) { // if the rightmost bit is 0
                printf("yes\n\n");
                value_count--;
            } else {
                printf("no\n\n");
                value_count++;
            }
        }

        printf("Column: %d Most common value: ", i);
        // we have more 0's and the gamma bit is 0
        if(value_count < 0) {
            printf("0\n");
            gamma |= (0 << i);
        } else { // we have more 1's and the gamma bit is 1
            printf("1\n");
            gamma |= (1 << i);
        }
    }

    // epsilon is bitwise complement of gamma;
    unsigned int epsilon = ~gamma;
    epsilon &= 0x00000FFF; // set upper 20 bits to 0, they'll be 1 by default since we only have 12 bits in our input
    /*
    char g_buf[33];
    char e_buf[33];
    itoa(gamma, g_buf, 2);
    itoa(epsilon, e_buf, 2);
    printf("Gamma: %d %s\nEpsilon: %d %s\nPower: %d\n", gamma, g_buf, epsilon, e_buf, gamma*epsilon);
    */
    printf("Gamma: %u\nEpsilon: %u\nPower: %u\n", gamma, epsilon, gamma*epsilon);

    return 0;
}
