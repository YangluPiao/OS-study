#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char* argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Error: should specify size\n");
    exit(1);
  }
  long size = atol(argv[1]);
  size <<= 20;
  printf("your input is (%ld * %ld) Byte\n", size, sizeof(int));
  int* a = (int*)malloc(size * sizeof(int));
  int b[size];
  for (int i = 0; i < size; i = (i + 1) % size) {
    if (a[i] < 100)
      a[i]++;
    if (b[i] < 100)
      b[i]++;
  }
  free(a);
}
