#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

int main(int argc, char **argv) {

    double basen = 22.0;
    double based = 7.0;

    int percision = 10000;

    int c;
    while ((c = getopt (argc, argv, ":n:d:p:")) != -1) {
        switch (c) {
            case 'n':
                basen = atof(optarg);
                break;
            case 'd':
                based = atof(optarg);
                break;
            case 'p':
                percision = atoi(optarg);
                break;
            case '?':
                fprintf(stderr, "%s: invalid option: '%c'\n", argv[0], optopt);
                return 1;
            case ':':
                fprintf(stderr, "%s: option requires value -- '%c'\n", argv[0], optopt);
                return 1;
            default:
                abort ();
        }
    }

    double base = basen / based;

    double target = base - floor(base);
    
    int num1 = 0;
    int den1 = 1;

    int num2 = 1;
    int den2 = 1;

    double comp = 0;

    int nummid = 0;
    int denmid = 0;

    for (int i = 0; i < percision; i++) {

        nummid = num1 + num2;
        denmid = den1 + den2;

        comp = (double) (nummid) / denmid;

        if (comp > target) {
            num2 = nummid;
            den2 = denmid;
        } else {
            num1 = nummid;
            den1 = denmid;
        }

    }

    double aprox = (double) ((((int) base) * denmid) + nummid) / denmid;

    printf("%f = %d/%d = %f\n", aprox, (((int) base) * denmid) + nummid, denmid, base);

}
