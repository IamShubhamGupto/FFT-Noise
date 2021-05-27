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
    int N = atoi(argv[1]);

    START_TIME_PERLIN = (float)clock() / CLOCKS_PER_SEC;

    PerlinNoise(0.5, 8, N);

    END_TIME_PERLIN = (float)clock() / CLOCKS_PER_SEC;

    START_TIME_SIMPLEX = (float)clock() / CLOCKS_PER_SEC;

    SimplexNoise(0.5, 8, N);

    END_TIME_SIMPLEX = (float)clock() / CLOCKS_PER_SEC;

    fprintf(stderr, "%f,%f\n", (END_TIME_PERLIN - START_TIME_PERLIN),
            (END_TIME_SIMPLEX - START_TIME_SIMPLEX));
    return 0;
}