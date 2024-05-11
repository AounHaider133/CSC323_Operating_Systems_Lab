#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

int radius = 1;

int total_points = 0;
int total_points_inside_circle = 0;
double *x;
double *y;
int num_of_points;

void *runner(void *);
int main(int argc, char *argv[]) {

  if (argc < 2) {
    printf("Usage:%s\n", argv[0]);
    return 1;
  }

  num_of_points = atoi(argv[1]);
  x = (double *)malloc((num_of_points) * sizeof(double));
  y = (double *)malloc((num_of_points) * sizeof(double));

  pthread_t t1;

  pthread_create(&t1, NULL, runner, NULL);

  pthread_join(t1, NULL);

  double estimated_pi = 4.0 * total_points_inside_circle / total_points;
  printf("Estimated Pi is: %lf\n", estimated_pi);

  // Actual value of pi
  double actual_pi = 3.141592653589793238;
  
  double accuracy = ((actual_pi - estimated_pi) / actual_pi) * 100;
  printf("Accuracy: %lf\n", accuracy);

  free(x);
  free(y);
  return 0;
}

void *runner(void *param) {
  for (int i = 0; i < num_of_points; i++) {
    x[i] = ((double)rand() / RAND_MAX) * 2 - 1;
    y[i] = ((double)rand() / RAND_MAX) * 2 - 1;
    total_points++;
    if ((x[i] * x[i] + y[i] * y[i]) <= (radius * radius))
      total_points_inside_circle++;
  }
  pthread_exit(NULL);
}

