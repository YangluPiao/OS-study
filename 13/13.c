#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Error: should specify size\n");
    exit(1);
  }
  int size = atoi(argv[1]);
  size <<= 30;
  printf("your input is %d B\n", size);
  int* a = (int*)malloc(size * sizeof(int));
  for (int i = 0; i < size; i = (i + 1) % size) {
    printf("%d\n", a[i]);
    sleep(1);
    //
  }
  free(a);
}
