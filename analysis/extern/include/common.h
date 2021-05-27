#pragma once

#include <stdio.h>
#include <stdlib.h>

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