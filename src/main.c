#include <time.h>

#include "../include/fractal.h"
#define COMP 4

// int DEBUG;
double START_TIME;
double END_TIME;
int main(int argc, char **argv)
{
    int DEBUG = 0;
    srand(time(0));
    if (argc < 3)
    {
        printf("Usage: ./bin/fft.out beta [input file]\n");
        printf("\nbeta - roughness factor\n");
        printf("N - Resolution\n");
        return EXIT_FAILURE;
    }
    struct timespec vartime;
    long time_elapsed_nanos;
    if (argc == 4)
    {
        if (strcmp(argv[3], "-d") == 0)
        {
            DEBUG = 1;
            START_TIME = (float)clock() / CLOCKS_PER_SEC;

            FFTNoise(DEBUG, atof(argv[1]), atoi(argv[2]), NULL);

            END_TIME = (float)clock() / CLOCKS_PER_SEC;
        }
        else
        {
            DEBUG = 0;
            FFTNoise(DEBUG, atof(argv[1]), atoi(argv[2]), argv[3]);
        }
    }
    else
    {
        FFTNoise(DEBUG, atof(argv[1]), atoi(argv[2]), NULL);
    }

    if (DEBUG)
        fprintf(stderr, "%f", (END_TIME - START_TIME) * 1000.0);
    return EXIT_SUCCESS;
}
