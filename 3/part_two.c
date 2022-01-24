/*
 Next, you should verify the life support rating, which can be determined by multiplying the oxygen generator rating by the CO2 scrubber rating.

Both the oxygen generator rating and the CO2 scrubber rating are values that can be found in your diagnostic report - finding them is the tricky part. Both values are located using a similar process that involves filtering out values until only one remains. Before searching for either rating value, start with the full list of binary numbers from your diagnostic report and consider just the first bit of those numbers. Then:

Keep only numbers selected by the bit criteria for the type of rating value for which you are searching. Discard numbers which do not match the bit criteria.
If you only have one number left, stop; this is the rating value for which you are searching.
Otherwise, repeat the process, considering the next bit to the right.
The bit criteria depends on which type of rating value you want to find:

For example, to determine the oxygen generator rating value using the same example diagnostic report from above:

Start with all 12 numbers and consider only the first bit of each number. There are more 1 bits (7) than 0 bits (5), so keep only the 7 numbers with a 1 in the first position: 11110, 10110, 10111, 10101, 11100, 10000, and 11001.
Then, consider the second bit of the 7 remaining numbers: there are more 0 bits (4) than 1 bits (3), so keep only the 4 numbers with a 0 in the second position: 10110, 10111, 10101, and 10000.
In the third position, three of the four numbers have a 1, so keep those three: 10110, 10111, and 10101.
In the fourth position, two of the three numbers have a 1, so keep those two: 10110 and 10111.
In the fifth position, there are an equal number of 0 bits and 1 bits (one each). So, to find the oxygen generator rating, keep the number with a 1 in that position: 10111.
As there is only one number left, stop; the oxygen generator rating is 10111, or 23 in decimal.
Then, to determine the CO2 scrubber rating value from the same example above:

Start again with all 12 numbers and consider only the first bit of each number. There are fewer 0 bits (5) than 1 bits (7), so keep only the 5 numbers with a 0 in the first position: 00100, 01111, 00111, 00010, and 01010.
Then, consider the second bit of the 5 remaining numbers: there are fewer 1 bits (2) than 0 bits (3), so keep only the 2 numbers with a 1 in the second position: 01111 and 01010.
In the third position, there are an equal number of 0 bits and 1 bits (one each). So, to find the CO2 scrubber rating, keep the number with a 0 in that position: 01010.
As there is only one number left, stop; the CO2 scrubber rating is 01010, or 10 in decimal.
Finally, to find the life support rating, multiply the oxygen generator rating (23) by the CO2 scrubber rating (10) to get 230.

Use the binary numbers in your diagnostic report to calculate the oxygen generator rating and CO2 scrubber rating, then multiply them together. What is the life support rating of the submarine? (Be sure to represent your answer in decimal, not binary.)
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static int lines = 1000; // bash cat input | wc -l
static int num_cols = 12; // bash head -n 1 input | wc -c

void get_col_vals(int *com_vals, int *ins);

int get_o2_rating(int *most_com_vals, int *ins);

int get_co2_rating(int *least_com_vals, int *ins);

int main(int argc, char **argv) {

    /*** setup ***/
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t line_len;

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

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
    /*** end setup ***/



    int o2_rating, co2_rating = 0;

    int com_vals[num_cols];

    get_col_vals(com_vals, inputs);

    o2_rating = get_o2_rating(com_vals, inputs);
    co2_rating = get_o2_rating(com_vals, inputs);

    printf("O2 Generator Rating: %u\nCO2 Scrubber Rating: %u\nLife Support rating: %u\n", o2_rating, co2_rating, o2_rating*co2_rating);

    return 0;
}

/*
 * Get the most common and least common bits in each column
 */
void get_col_vals(int com_vals[num_cols], int ins[lines]) {

    int value_count = 0;
    int i, j, k = 0;

    // for each column, starting from leftmost
    for(i = num_cols-1; i >= 0; i--) {

        value_count = 0;

        // for each value in inputs
        for(j = 0; j < lines; j++) {

            // we bit shift to get the next bit column from the input values
            unsigned int shift = ins[j] >> i;
            if(shift % 2 == 0) { // if the rightmost bit is 0
                value_count--;
            } else {
                value_count++;
            }
        }

        
        if(value_count == 0) { // equal occurance
            com_vals[k] = -1;
        } else if(value_count < 0) { // 0 is most common
            com_vals[k] = 0;
        } else { // 1 is most common
            com_vals[k] = 1;
        }
        k++; // prepare to set the next element in the com_vals array
    }

}

int vals_to_int(int vals[num_cols], bool o2) {
    int ret = 0;
    int j = 0; // so we can shift right to left

    // go through list from right to left adding that bit to ret in the
    // correct index
    for(int i = num_cols-1; i >= 0; i--, j++) {

        switch(vals[i]) {
            case 0:
            case 1:
                ret |= (vals[i] << j);
                break;
            case -1:
                if(o2) {
                    ret |= (1 << j);
                } else { // co2
                    ret |= 0;
                }
                break;
        }

    }

    return(ret);
}

/*
To find oxygen generator rating, determine the most common value (0 or 1) in
the current bit position, and keep only numbers with that bit in that position.
If 0 and 1 are equally common, keep values with a 1 in the position being
considered.
*/
int get_o2_rating(int com_vals[num_cols], int ins[lines]) {

    // So, with this filtering method, we're basically looking for a value that
    // just matches our filter. Meaning if our filter is 1101-1 then we're 
    // looking for a number that matches 11011 with all the bits in those columns
    // which means that the filter is basically our number right?
    // If so, I just need to convert the filter to the proper number and verify
    // that I have that number in the input list and that should give me the o2

    int o2_filter = vals_to_int(com_vals, true);
    for(int i = 0; i < lines; i++) {
        if(ins[i] == o2_filter)
            return(ins[i]);
    }

    // my logic was hella wrong
    return -1;
}

/*
To find CO2 scrubber rating, determine the least common value (0 or 1) in the
current bit position, and keep only numbers with that bit in that position.
If 0 and 1 are equally common, keep values with a 0 in the position being
considered.
*/

int get_co2_rating(int com_vals[num_cols], int ins[lines]) {

    int least_com_vals[num_cols];
    for(int i = 0; i < num_cols; i++) {
        switch(com_vals[i]) {
            case 0:
            case 1:
                least_com_vals[i] = (~com_vals[i]);
                break;
            case -1:
                least_com_vals[i] = 0;
                break;
        }
    }

    int co2_filter = vals_to_int(least_com_vals, true);
    for(int i = 0; i < lines; i++) {
        if(ins[i] == co2_filter)
            return(ins[i]);
    }

    // my logic was hella wrong
    return -1;
}
