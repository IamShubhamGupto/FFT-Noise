#include <time.h>
#include "./perlin.c"

double START_TIME;
double END_TIME;


int main() {
    int N = 4096;
    int x, y, i;

    START_TIME = (float)clock() / CLOCKS_PER_SEC;
    
        for(y=0; y<N; y++)
            for(x=0; x<N; x++) 
                perlin2d(x, y, 0.5, 8);
            

    END_TIME = (float)clock() / CLOCKS_PER_SEC;

    fprintf(stderr, "%f %f %f",END_TIME, START_TIME, (END_TIME - START_TIME) * 1000);
    return 0;
}