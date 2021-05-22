#include "fft.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <time.h>
#define DEBUG 1
#define DO_FFT 1
#define DO_IFFT -1
#define ENABLE_LOW_PASS_BUTTERWORTH_FILTER 0
#define FREQUENCY_FILTER 1
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

int powerOf2(unsigned int v)
{
    return v > 0 && (v & (v - 1)) == 0;
}

unsigned int toRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    return (r) | (g << 8) | (b << 16) | (a << 24);
}

/**
 * refer 
 * http://users.cs.cf.ac.uk/Dave.Marshall/CM0268/PDF/09_CM0268_Frequence_Space.pdf
 * for generate_lpbf and apply_filter
 */
#if ENABLE_LOW_PASS_BUTTERWORTH_FILTER
void generate_lpbf(float **filter, float **matreal, float **matim, int lgth, int wdth, int w0, int n)
{
    int i;
    int j;
    float term;
    for (i = 0; i < lgth; i++)
    {
        for (j = 0; j < wdth; j++)
        {
            term = pow(((matreal[i][j] * matreal[i][j]) + (matim[i][j] * matim[i][j])) / (w0 * w0), n);
            filter[i][j] = (1.0 + term);
        }
    }
}
void apply_lpbf(float **filter, float **mat, int lgth, int wdth)
{
    int i;
    int j;
    for (i = 0; i < lgth; i++)
    {
        for (j = 0; j < wdth; j++)
        {
            mat[i][j] /= filter[i][j];
        }
    }
}
#endif
void apply_filter_f(float *frequency, float **mat, int lgth, int wdth, float beta)
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

void testifft(float **m_real, float **m_imag, int x, int y, int comp)
{
    unsigned int *modfft;
    int i, j, res;
    ifft(m_real, m_imag, x, y);

    fftshift(m_real, x, y);

    modfft = (unsigned int *)malloc(sizeof(unsigned int) * x * y * comp);

    for (j = 0; j < y; ++j)
    {
        for (i = 0; i < x; ++i)
        {
            unsigned char v = (unsigned char)m_real[i][j];
            modfft[i + j * x] = toRGBA(v, v, v, 255);
        }
    }

    res = stbi_write_png("bin/fractal_noise.png", x, y, comp, modfft, 0);

    if (!res)
    {
        printf("Error saving file\n");
    }
    free(modfft);
}
void testfft(float beta)
{
    if (DEBUG)
    {
        printf("beta - %f\n", beta);
    }
    int N = 256;
    unsigned char *data;
    unsigned int *modfft;
    float **m_real;
    float **modulus;
    float **m_imag;
    float **filter;
    float *frequency;
    int x, y, i, j, comp, res, offset;

    x = N;
    y = N;
    comp = 4;

    int size = x * y * 4;

    data = (unsigned char *)malloc(sizeof(unsigned char) * size);

    for (i = 0; i < size; i+=4) {

        unsigned char col = rand() % 255;

        data[i] = col;
        data[i + 1] = col;
        data[i + 2] = col;
        data[i + 3] = 1;

    }

    if (x != y || !powerOf2(x))
    {
        printf("Error: Image dimensions must be a power of 2\n");
        return;
    }

    m_real = malloc2d(x, y);
    modulus = malloc2d(x, y);
    filter = malloc2d(x, y);
    frequency = (float *)malloc(sizeof(float) * x);
    printf("width %d, height %d\n", x, y);

    offset = 0;
    for (j = 0; j < y; ++j)
    {
        for (i = 0; i < x; ++i)
        {
            int off = i + j * x + offset;
            m_real[i][j] = (float)data[off] + (float)data[off + 1] + (float)data[off + 2];
            m_real[i][j] /= comp - 1;
            offset += comp - 1;
        }
    }

    m_imag = malloc2d(x, y);

    // perform fast fourier transform on the 2d signal (red channel)
    fft(m_real, m_imag, x, y);

    fftfreq(x, 1.0, frequency);
#if ENABLE_LOW_PASS_BUTTERWORTH_FILTER
    generate_lpbf(filter, m_real, m_imag, x, y, w0, beta);
    apply_lpbf(filter, m_real, x, y);
    apply_lpbf(filter, m_imag, x, y);
#endif

#if FREQUENCY_FILTER
    apply_filter_f(frequency, m_real, x, y, beta);
    apply_filter_f(frequency, m_imag, x, y, beta);
#endif

    //compute the modulus of the fourier transform
    mod(modulus, m_real, m_imag, x, y);

    //shift the fourier transform to move the zero frequency in center
    fftshift(modulus, x, y);

    center(modulus, m_real, x, y);

    modfft = (unsigned int *)malloc(sizeof(unsigned int) * x * y * comp);

    for (j = 0; j < y; ++j)
    {
        for (i = 0; i < x; ++i)
        {
            unsigned char v = (unsigned char)m_real[i][j];
            modfft[i + j * x] = toRGBA(v, v, v, 255);
        }
    }

    res = stbi_write_png("bin/spectrum.png", x, y, comp, modfft, 0);

    if (!res)
    {
        printf("Error saving file\n");
    }
    
    testifft(m_real, m_imag, x, y, comp);

    free2d(modulus);
    free2d(m_imag);
    free2d(m_real);
    free(modfft);
    free2d(filter);
    free(frequency);
}

int main(int argc, char **argv)
{
    srand(time(0));
    if (argc < 2)
    {
        printf("Usage: ./bin/fft.out beta\n");
        printf("\nbeta - roughness factor\n");
        return EXIT_FAILURE;
    }

    testfft(atof(argv[1]));

    return EXIT_SUCCESS;
}
