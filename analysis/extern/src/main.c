#include <time.h>
#include <stdlib.h>
#include "../include/perlin.h"
#include "../include/simplex.h"
// #include "../../../include/fractal.h"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("ERROR: need 1 integer argument\n");
        return 1;
    }
    float START_TIME_PERLIN;
    float END_TIME_PERLIN;
    float START_TIME_SIMPLEX;
    float END_TIME_SIMPLEX;
    float START_TIME_FFT;
    float END_TIME_FFT;
    int N = atoi(argv[1]);
    int x, y, i;

    START_TIME_PERLIN = (float)clock() / CLOCKS_PER_SEC;

    PerlinNoise(0.5, 8, N);

    END_TIME_PERLIN = (float)clock() / CLOCKS_PER_SEC;

    START_TIME_SIMPLEX = (float)clock() / CLOCKS_PER_SEC;

    SimplexNoise(N);

    END_TIME_SIMPLEX = (float)clock() / CLOCKS_PER_SEC;

    START_TIME_FFT = (float)clock() / CLOCKS_PER_SEC;

    FFTNoise(1, 2.0, N, NULL);

    END_TIME_FFT = (float)clock() / CLOCKS_PER_SEC;

    fprintf(stderr, "%d %f %f %f\n", N, (END_TIME_PERLIN - START_TIME_PERLIN) * 1000,
            (END_TIME_SIMPLEX - START_TIME_SIMPLEX) * 1000, (END_TIME_FFT - START_TIME_FFT) * 1000);
    return 0;
}