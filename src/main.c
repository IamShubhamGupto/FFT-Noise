
#include "./fft-noise.h"

int main(int argc, char **argv)  {
  srand(time(0));

    if (argc < 3) {
        printf("Usage: ./bin/fft.out beta [input file]\n");
        printf("\nbeta - roughness factor\n");
        printf("N - Resolution\n");
        return EXIT_FAILURE;
    }

    if(argc >= 4 && strcmp(argv[3], "-d") == 0) {
        DEBUG = 1;
    } else {
        DEBUG = 0;
    }

    if(argc == 5) {
        FFTN_useImage(argv[4]);
    }

    START_TIME = (float)clock() / CLOCKS_PER_SEC;
    FFTN_noise(atof(argv[1]), atoi(argv[2]));
    END_TIME = (float)clock() / CLOCKS_PER_SEC;
 

  if (DEBUG)
    fprintf(stderr, "%f", (END_TIME - START_TIME));
  return EXIT_SUCCESS;
}
