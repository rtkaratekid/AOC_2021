/*
You need to use the binary numbers in the diagnostic report to generate two new binary numbers (called the gamma rate and the epsilon rate). The power consumption can then be found by multiplying the gamma rate by the epsilon rate.

Each bit in the gamma rate can be determined by finding the most common bit in the corresponding position of all numbers in the diagnostic report. For example, given the following diagnostic report:

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

    // Now we have all the input in memory and don't need to loop through the file anymore
    printf("calculations\n");
    int gamma = 0;
    int epsilon = 0;
    int columns = line_len - 1; //assuming all columns are the same length
    for(int i = 0; i < columns; i++) {
        // get the most common/least common value in column
        int value_count = 0;
        for(int j = 0; j < lines; j++) {
            // we bit shift to get the next bit from the input value
            if(inputs[j] >> i % 2 == 0) { // means the first bit is 0
                value_count--;
            } else {
                value_count++;
            }
        }

        // if gamma count is negative, then we have more 0's and the gamma bit is 0
        if(value_count < 0) {
            gamma |= (0 << i);
            epsilon |= (1 << i);
        } else { // if gamma count is positive, then we have more 1's and the gamma bit is 1
            gamma |= (1 << i);
            epsilon |= (0 << i);
        }
    }

    printf("Gamma: %d\nEpsilon: %d\nMulitplied: %d\n", gamma, epsilon, gamma*epsilon);

    return 0;
}
