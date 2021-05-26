#include <stdio.h>
#include <string.h>
#include <time.h>

#include "../include/fft.h"
#include "../include/libattopng/libattopng.h"

#define COMP 4
#define RGBA(r, g, b, a) ((r) | ((g) << 8) | ((b) << 16) | ((a) << 24))

int DEBUG;
double START_TIME;
double END_TIME;

void free2d(float **p) {
  free(p[0]);
  free(p);
}

float **malloc2d(int v, int h) {
  int i;
  float **m;
  float *p;

  m = (float **)malloc(sizeof(float *) * v);
  p = (float *)malloc(sizeof(float) * h * v);

  for (i = 0; i < v; i++, p += h) {
    m[i] = p;
  }

  return m;
}

float *malloc1D(int N) { return (float *)malloc(sizeof(float) * N); }

int powerOf2(unsigned int v) { return v > 0 && (v & (v - 1)) == 0; }


void applyFilter(float *frequency, float **mat, int lgth, int wdth,
                 float beta) {
  int i;
  int j;
  float **radial_freq = malloc2d(lgth, wdth);

  for (i = 0; i < lgth; ++i) {
    for (j = 0; j < wdth; ++j) {
      radial_freq[i][j] =
          sqrt((frequency[i] * frequency[i]) + (frequency[j] * frequency[j]));
      if (radial_freq[i][j] == 0) {
        mat[i][j] = 0.0;
      } else {
        mat[i][j] = mat[i][j] / (pow(radial_freq[i][j], beta) * lgth);
      }
    }
  }
  free2d(radial_freq);
}

float* getMinMax(float **data, int x, int y) {
  int i, j;
  float max = data[0][0], min = data[0][0];
  for (i = 0; i < x; ++i) {
    for (j = 0; j < y; ++j) {
        if (max < data[i][j]) {
            max = data[i][j];
        }
    }
  }

  for (i = 0; i < x; ++i) {
    for (j = 0; j < y; ++j) {
        if (min > data[i][j]) {
            min = data[i][j];
        }
    }
  }

  float* minmax = malloc1D(2);
  minmax[0] = min;
  minmax[1] = max;
  return minmax;
}

void saveImage(float **data, int x, int y) {
    float* minMax = getMinMax(data, x, y);

    libattopng_t *png = libattopng_new(x, y, PNG_RGBA);

    int i, j;
    for (i = 0; i < x; ++i)
    {
        for (j = 0; j < y; ++j)
        {
            unsigned char v = (unsigned char)((data[i][j] - minMax[0]) / (minMax[1] - minMax[0]) * 255.0);
            libattopng_set_pixel(png, i, j, RGBA(v, v, v, 255));
        }
    }

    libattopng_save(png, "output/fractal_noise.png");

    libattopng_destroy(png);
    free(minMax);
}

void makeWhiteNoise(int N, float **m_real) {
  int offset = 0, i, j;

  for (j = 0; j < N; ++j) {
    for (i = 0; i < N; ++i) {

      unsigned char col = rand() % 255;

      m_real[i][j] =
          (float)col + (float)col + (float)col;
      m_real[i][j] /= COMP - 1;
      offset += COMP - 1;
    }
  }
}

void FFTNoise(float beta, int N) {
  float **m_real = malloc2d(N, N);
  float **modulus = malloc2d(N, N);
  float **m_imag = malloc2d(N, N);
  float **filter = malloc2d(N, N);
  float *frequency = malloc1D(N);


  if(!DEBUG) {
    if (!powerOf2(N)) {
        printf("Error: N must be a power of 2\n");
        return;
    }

    printf("Beta : %f\nwidth : %d\nheight : %d\n", beta, N, N);
  }

  makeWhiteNoise(N, m_real);

  fft(m_real, m_imag, N, N);
  fftfreq(N, 1.0, frequency);
  
  applyFilter(frequency, m_real, N, N, beta);
  applyFilter(frequency, m_imag, N, N, beta);

  fftshift(m_real, N, N);

  ifft(m_real, m_imag, N, N);

  if (!DEBUG) {
    saveImage(m_real, N, N);
  }
    

  free2d(modulus);
  free2d(m_imag);
  free2d(m_real);
  free2d(filter);
  free(frequency);

}

int main(int argc, char **argv)  {
  srand(time(0));

    if (argc < 3) {
        printf("Usage: ./bin/fft.out beta [input file]\n");
        printf("\nbeta - roughness factor\n");
        printf("N - Resolution\n");
        return EXIT_FAILURE;
    }

    if(argc == 4 && strcmp(argv[3], "-d") == 0) {
        DEBUG = 1;
    } else {
        DEBUG = 0;
    }

    START_TIME = (float)clock() / CLOCKS_PER_SEC;
    FFTNoise(atof(argv[1]), atoi(argv[2]));
    END_TIME = (float)clock() / CLOCKS_PER_SEC;
 

  if (DEBUG)
    fprintf(stderr, "%f", (END_TIME - START_TIME) * 1000.0);
  return EXIT_SUCCESS;
}
