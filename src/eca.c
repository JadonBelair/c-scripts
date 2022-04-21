// linux only
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <locale.h>
#include <wchar.h>
#include <getopt.h>
#include "eca.h"

int main(int argc, char *argv[] ) {
    
    setlocale(LC_CTYPE, "");
    
    int r = 0;

    int ruleset = 129;

    int opt;
    while((opt = getopt(argc, argv, ":r:s")) != -1) { 
        switch(opt) 
        { 
            case 'r': 
                ruleset = atoi(optarg);
                if (ruleset < 0 || ruleset > 255) {
                    fprintf(stderr, "%s: option value out of range -- 'r'\n", argv[0]);
                    return 1;
                }
                break; 
            case 's': 
                r = 1;
                break; 
            case ':': 
                fprintf(stderr, "%s: option requires an argument -- '%c'\n", argv[0], optopt);
                return 1;
                break; 
            case '?': 
                fprintf(stderr, "unknown option: %c\n", optopt);
                return 1;
                break; 
        } 
    }

    system("clear");

    int grid[COLS];

    for (int i =0; i < COLS; i++) {
        grid[i] = 0;
    }

    if (r) {
        // random first row
        srand(time(NULL) * time(NULL));
        for (int i = 0; i < COLS; i++) {
            grid[i] = ((double) rand() / RAND_MAX) > 0.5 ? 1 : 0;
        }
    } else {
        // one in middle of first row
        grid[COLS/2] = 1;
    }

    int clone[COLS];

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int left = ((j == 0) ? grid[COLS-1] : grid[j-1]);
            int center = grid[j];
            int right = ((j == (COLS - 1)) ? grid[0] : grid[j+1]);

            int next_cell = generate(left, center, right, ruleset);

            clone[j] = next_cell;

            wprintf(L"%lc", grid[j] == 1 ? BLACK : WHITE);
        }

        copy(clone, grid, COLS);

        wprintf(L"%lc", 0xA);
    }

    return 0;
}

int generate(int left, int center, int right, int rule) {
    int shift = left << 2 | center << 1 | right;
    int newval = (rule >> shift) & 1;

    return newval;
}

void copy(int source[], int dest[], int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = source[i];
    }
}
