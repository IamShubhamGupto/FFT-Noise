// Modified form https://github.com/karimnaaji/fft

#include <math.h>
#include <stdlib.h>


#define SWAP(x, y)        \
    do                    \
    {                     \
        typeof(x) _x = x; \
        typeof(y) _y = y; \
        x = _y;           \
        y = _x;           \
    } while (0);
#define IFFT -1
#define FFT 1
#define FFT2D 2

static void normalise(float **mat, int lgth, int wdth)
{
    int i, j;
    float max, min;

    min = mat[0][0];
    max = mat[0][0];

    for (i = 0; i < lgth; ++i)
        for (j = 0; j < wdth; ++j)
        {
            if (mat[i][j] < min)
            {
                min = mat[i][j];
            }

            if (mat[i][j] > max)
            {
                max = mat[i][j];
            }
        }

    for (i = 0; i < lgth; ++i)
        for (j = 0; j < wdth; ++j)
        {
            mat[i][j] = ((mat[i][j] - min) / (max - min)) * 255.0;
        }
}

static void arrange(int begin, int end, float *p1)
{
    int i = 0;
    while (begin != end)
    {
        p1[i] = begin;
        ++i;
        ++begin;
    }
}

static void fftfreq(int n, float d, float *results)
{
    int i;
    float val = (n * d);
    //float *results = (float *)malloc(sizeof(float) * n);
    int N = ((n - 1) / 2) + 1;
    float *p1 = (float *)malloc(sizeof(float) * N);
    arrange(0, N, p1);
    for (i = 0; i < N; ++i)
    {
        results[i] = p1[i];
    }
    float *p2 = (float *)malloc(sizeof(float) * (N));
    arrange(-(n / 2), 0, p2);
    for (i = N; i < n; ++i)
    {
        results[i] = p2[i - N];
    }
    for (i = 0; i < n; ++i)
    {
        results[i] /= val;
    }
    free(p1);
    free(p2);
}

static void fourrier(float data[], unsigned long nn[], int ndim, int isign)
{
    int idim;
    unsigned long i1, i2, i3, i2rev, i3rev, ip1, ip2, ip3, ifp1, ifp2;
    unsigned long ibit, k1, k2, n, nprev, nrem, ntot;
    float tempi, tempr;
    double theta, wi, wpi, wpr, wr, wtemp;

    for (ntot = 1, idim = 1; idim <= ndim; idim++)
    {
        ntot *= nn[idim];
    }

    nprev = 1;

    for (idim = ndim; idim >= 1; idim--)
    {
        n = nn[idim];
        nrem = ntot / (n * nprev);
        ip1 = nprev << 1;
        ip2 = ip1 * n;
        ip3 = ip2 * nrem;
        i2rev = 1;

        for (i2 = 1; i2 <= ip2; i2 += ip1)
        {
            if (i2 < i2rev)
            {
                for (i1 = i2; i1 <= i2 + ip1 - 2; i1 += 2)
                {
                    for (i3 = i1; i3 <= ip3; i3 += ip2)
                    {
                        i3rev = i2rev + i3 - i2;
                        SWAP(data[i3], data[i3rev]);
                        SWAP(data[i3 + 1], data[i3rev + 1]);
                    }
                }
            }

            ibit = ip2 >> 1;

            while (ibit >= ip1 && i2rev > ibit)
            {
                i2rev -= ibit;
                ibit >>= 1;
            }

            i2rev += ibit;
        }

        ifp1 = ip1;

        while (ifp1 < ip2)
        {
            ifp2 = ifp1 << 1;
            theta = isign * 6.28318530717959 / (ifp2 / ip1);
            wtemp = sin(0.5 * theta);
            wpr = -2.0 * wtemp * wtemp;
            wpi = sin(theta);
            wr = 1.0;
            wi = 0.0;

            for (i3 = 1; i3 <= ifp1; i3 += ip1)
            {
                for (i1 = i3; i1 <= i3 + ip1 - 2; i1 += 2)
                {
                    for (i2 = i1; i2 <= ip3; i2 += ifp2)
                    {
                        k1 = i2;
                        k2 = k1 + ifp1;
                        tempr = (float)wr * data[k2] - (float)wi * data[k2 + 1];
                        tempi = (float)wr * data[k2 + 1] + (float)wi * data[k2];
                        data[k2] = data[k1] - tempr;
                        data[k2 + 1] = data[k1 + 1] - tempi;
                        data[k1] += tempr;
                        data[k1 + 1] += tempi;
                    }
                }

                wr = (wtemp = wr) * wpr - wi * wpi + wr;
                wi = wi * wpr + wtemp * wpi + wi;
            }
            ifp1 = ifp2;
        }
        nprev *= n;
    }
}

static void _fft(float **matreal, float **matimg, int lgth, int wdth, int direction)
{
    int i, j, posx, posy;
    float *data, *freqreal, *freqim;
    unsigned long *nn;

    data = (float *)malloc(sizeof(float) * (2 * wdth * lgth) + 1);
    freqreal = (float *)malloc(sizeof(float) * (wdth * lgth));
    freqim = (float *)malloc(sizeof(float) * (wdth * lgth));
    nn = (unsigned long *)malloc(sizeof(unsigned long) * (FFT2D + 1));

    nn[1] = lgth;
    nn[2] = wdth;

    for (i = 0; i < lgth; i++)
        for (j = 0; j < wdth; j++)
        {
            data[2 * (i * lgth + j) + 1] = matreal[i][j];
            data[2 * (i * lgth + j) + 2] = matimg[i][j];
        }

    fourrier(data, nn, FFT2D, direction > 0 ? FFT : IFFT);

    for (i = 0; i < (wdth * lgth); i++)
    {
        freqreal[i] = data[(2 * i) + 1];
        freqim[i] = data[(2 * i) + 2];
    }

    for (i = 0; i < (wdth * lgth); i++)
    {
        posy = (int)(i / wdth);
        posx = (int)(i % wdth);
        matreal[posy][posx] = freqreal[i];
        matimg[posy][posx] = freqim[i];
    }

    free(data);
    free(freqreal);
    free(freqim);
    free(nn);
}

static void fft(float **matreal, float **matimg, int lgth, int wdth) {
    _fft(matreal, matimg, lgth, wdth, 1);
}


static void ifft(float **matreal, float **matimg, int lgth, int wdth) {
    _fft(matreal, matimg, lgth, wdth, -1);  
}

static void fftshift(float **in, int length, int width)
{
    int i, j;

    for (i = 0; i < length; ++i)
    {
        for (j = 0; j < width; ++j)
        {
            if (i < length / 2)
            {
                if (j < width / 2)
                {
                    in[i][j] = in[i + length / 2][j + width / 2];
                }
                else
                {
                    in[i][j] = in[i + length / 2][j - width / 2];
                }
            }
            else
            {
                if (j < width / 2)
                {
                    in[i][j] = in[i - length / 2][j + width / 2];
                }
                else
                {
                    in[i][j] = in[i - length / 2][j - width / 2];
                }
            }
        }
    }
}
