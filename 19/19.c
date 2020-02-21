#define _GNU_SOURCE
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sched.h>

void measure(void (*fn)(int), int x, int times) {
  struct timeval t1, t2;
  gettimeofday(&t1, NULL);
  for (int i = 0; i < times; i++) {
    fn(x);
  }
  gettimeofday(&t2, NULL);
  double elapse = (t2.tv_sec - t1.tv_sec) * 1e6;
  elapse += (t2.tv_usec - t1.tv_usec);
  elapse *= 1e3; // convert to nanoseconds
  printf("per access: %f ns\n", elapse / (times * x));
}

void test(const int num_pages) {
  const int page_size = getpagesize();
  const int jump = page_size / sizeof(int);
  int* a = (int*)calloc(num_pages * jump, sizeof(int));
  for (int i = 0; i < num_pages * jump; i += jump)
    a[i] += 1;
  free(a);
}

int main(int argc, char* argv[]) {
  cpu_set_t set;
  CPU_ZERO(&set);
  CPU_SET(0, &set);
  int num_pages = atoi(argv[1]);
  int num_trials = atoi(argv[2]);
  measure(&test, num_pages, num_trials);
}
