#include <time.h>

#include "../include/fft.h"
#include "../include/stb_image.h"
#include "../include/stb_image_write.h"

#define COMP 4

int DEBUG;
double START_TIME;
double END_TIME;

void free2d(float **p)
{
    free(p[0]);
    free(p);
}

float **malloc2d(int v, int h)
{
    int i;
    float **m;
    float *p;

    m = (float **)malloc(sizeof(float *) * v);
    p = (float *)malloc(sizeof(float) * h * v);

    for (i = 0; i < v; i++, p += h)
    {
        m[i] = p;
    }

    return m;
}

float *malloc1D(int N)
{
    return (float *)malloc(sizeof(float) * N);
}

int powerOf2(unsigned int v)
{
    return v > 0 && (v & (v - 1)) == 0;
}

unsigned int toRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    return (r) | (g << 8) | (b << 16) | (a << 24);
}

void applyFilter(float *frequency, float **mat, int lgth, int wdth, float beta)
{
    int i;
    int j;
    float **radial_freq = malloc2d(lgth, wdth);
    float term;
    for (i = 0; i < lgth; ++i)
    {
        for (j = 0; j < wdth; ++j)
        {
            radial_freq[i][j] = sqrt((frequency[i] * frequency[i]) + (frequency[j] * frequency[j]));
            if (radial_freq[i][j] == 0)
            {
                mat[i][j] = 0.0;
            }
            else
            {
                mat[i][j] = mat[i][j] / (pow(radial_freq[i][j], beta) * lgth);
            }
        }
    }
    free2d(radial_freq);
}

void saveImage(float **data, int x, int y)
{
    unsigned int *temp = (unsigned int *)malloc(sizeof(unsigned int) * x * y * COMP);

    int i, j;
    for (i = 0; i < x; ++i)
    {
        for (j = 0; j < y; ++j)
        {
            unsigned char v = (unsigned char)data[i][j];
            temp[i + j * x] = toRGBA(v, v, v, 255);
        }
    }

    int res = stbi_write_png("output/fractal_noise.png", x, y, COMP, temp, 0);

    if (!res)
    {
        printf("Error saving file\n");
        free(temp);
        exit(1);
    }
}

unsigned int hash(unsigned int x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}

unsigned char *initRandInput(int N)
{
    int size = N * N * 4;

    unsigned char *data = (unsigned char *)malloc(sizeof(unsigned char) * size);
    unsigned int *rand_img = (unsigned int *)malloc(sizeof(unsigned int) * size);

    int i, j;
    for (i = 0, j = 0; i < size; i += 4, j++)
    {
        unsigned char col = rand() % 255;

        data[i] = col;
        data[i + 1] = col;
        data[i + 2] = col;
        data[i + 3] = 1;
        rand_img[j] = toRGBA(col, col, col, 255);
    }
    
    
    if(!DEBUG) {
        int res = stbi_write_png("output/original_rand.png", N, N, COMP, rand_img, 0);

        if (!res)
        {
            printf("Error saving file\n");
            free(data);
            free(rand_img);
            exit(0);
        }
    }
        

    free(rand_img);
    return data;
}

unsigned char *initFileInput(int *N, char *filename)
{
    FILE *file = fopen(filename, "rb");

    if (!file)
    {
        printf("Could not open file: %s", filename);
        fclose(file);
        exit(1);
    }

    int comp, x, y;
    unsigned char *data = stbi_load_from_file(file, &x, &y, &comp, STBI_rgb_alpha);

    if (x != y)
    {
        printf("Error: Image must be a square.");
        fclose(file);
        exit(1);
    }

    *N = x;

    fclose(file);
    return data;
}

void dataToComplexReal(int N, float **m_real, unsigned char *data)
{
    int offset = 0, i, j;

    for (j = 0; j < N; ++j)
    {
        for (i = 0; i < N; ++i)
        {
            int off = i + j * N + offset;
            m_real[i][j] = (float)data[off] + (float)data[off + 1] + (float)data[off + 2];
            m_real[i][j] /= COMP - 1;
            offset += COMP - 1;
        }
    }
}

void FFTNoise(float beta, int N, char *filename) {
    unsigned char *data;
    unsigned int *modfft;
    float **m_real = malloc2d(N, N);
    float **modulus = malloc2d(N, N);
    float **m_imag = malloc2d(N, N);
    float **filter = malloc2d(N, N);
    float *frequency = malloc1D(N);

    int i, j, res, offset;

    data = filename == NULL ? initRandInput(N) : initFileInput(&N, filename);

    if (!powerOf2(N))
    {
        printf("Error: Image dimensions must be a power of 2\n");
        stbi_image_free(data);
        return;
    }

    printf("Beta : %f\nwidth : %d\nheight : %d\n", beta, N, N);

    dataToComplexReal(N, m_real, data);

    fft(m_real, m_imag, N, N);
    fftfreq(N, 1.0, frequency);

    applyFilter(frequency, m_real, N, N, beta);
    applyFilter(frequency, m_imag, N, N, beta);

    if (!DEBUG)
    {
        mod(modulus, m_real, m_imag, N, N);
        fftshift(modulus, N, N);
        center(modulus, m_real, N, N);
        saveImage(m_real, N, N);
    }

    ifft(m_real, m_imag, N, N);
    fftshift(m_real, N, N);

    if (!DEBUG)
        saveImage(m_real, N, N);

    free2d(modulus);
    free2d(m_imag);
    free2d(m_real);
    free(modfft);
    free2d(filter);
    free(frequency);

    if (filename != NULL)
    {
        stbi_image_free(data);
    }
}

int main(int argc, char **argv)
{
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

            FFTNoise(atof(argv[1]), atoi(argv[2]), NULL);

            END_TIME = (float)clock() / CLOCKS_PER_SEC;
        }
        else
        {
            DEBUG = 0;
            FFTNoise(atof(argv[1]), atoi(argv[2]), argv[3]);
        }
    }
    else
    {
        FFTNoise(atof(argv[1]), atoi(argv[2]), NULL);
    }

    if (DEBUG)
        fprintf(stderr, "%f", (END_TIME - START_TIME) * 1000.0);
    return EXIT_SUCCESS;
}
