#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double distance(double x1, double y1, double x2, double y2) {
  double dx = fabs(x2-x1);
  double dy = fabs(y2-y1);
  if (dx > 0.5) {
    dx = 1.0-dx;
  }
  return sqrt(dx*dx+dy*dy);
}

double potential(double *x, double *y, int i, double xcur) {
  double dmin = distance(x[0], y[0], xcur, y[i]);
  double dcur;
  int j;

  for (j = 1; j < i; ++j) {
    dcur = distance(x[j], y[j], xcur, y[i]);
    if (dcur < dmin) {
      dmin = dcur;
    }
  }

  return -dmin;
}

double find_minimum(double *x, double *y, int i) {
  double dx = 0.001;
  double xmax = 1.0;
  double xcur = 0.0;
  double pcur = 0.0;
  double xopt = 0.0;
  double popt = 0.0;

  while (dx > 1e-9) {
    while (xcur < xmax) {
      pcur = potential(x, y, i, xcur);
      // printf("%f, %f, %f\n", xcur, y[i], pcur);
      if (pcur < popt) {
        xopt = xcur;
        popt = pcur;
      }
      xcur += dx;
    }
    xcur = xopt-dx;
    xmax = xopt+dx;
    dx /= 10.0;
  }

  if (xopt > 1.0) {
    xopt -= 1.0;
  } else if (xopt < 0.0) {
    xopt += 1.0;
  }

  return xopt;
}

int main(int argc, char **argv) {
  int length = 1024;
  double *x = malloc(length*sizeof(double));
  double *y = malloc(length*sizeof(double));
  double dy;

  if (argc < 2) {
    printf("Argument missing.\n");
    exit(-1);
  }

  dy = atof(argv[1]);

  if (dy <= 0.0) {
    printf("Argument invalid.\n");
    exit(-1);
  }

  int i;

  for (i = 0; i < length; ++i) {
    y[i] = (double)i*dy;
  }

  x[0] = 0;

  for (i = 1; i < length; ++i) {
    x[i] = find_minimum(x, y, i);
    printf("%f, %f\n", x[i], y[i]);
  }

  free(x);
  free(y);
}
