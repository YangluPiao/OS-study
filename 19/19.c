#define _GNU_SOURCE
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sched.h>

int main(int argc, char* argv[]) {
  // use one cpu
  cpu_set_t set;
  CPU_ZERO(&set);
  CPU_SET(0, &set);
  if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &set) == -1)
    exit(1);

  int num_pages = atoi(argv[1]);
  int num_trials = atoi(argv[2]);

  const int page_size = getpagesize();
  const int jump = page_size / sizeof(int);

  int* a = (int*)calloc(num_pages * jump, sizeof(int));

  struct timeval t1, t2;
  gettimeofday(&t1, NULL);

  for (int i = 0; i < num_trials; i++) {
    for (int j = 0; j < num_pages * jump; j += jump) {
      a[j] += 1;
    }
  }

  gettimeofday(&t2, NULL);
  double elapse = (t2.tv_sec - t1.tv_sec) * 1e6;
  elapse += (t2.tv_usec - t1.tv_usec);
  elapse *= 1e3; // convert to nanoseconds
  printf("num_pages: %4d, time per access: %lf ns\n",
      num_pages, elapse / ((double)(num_pages) * num_trials));

  // don't count this in timing!!
  free(a);
}
