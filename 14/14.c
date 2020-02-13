#include <stdio.h>
#include <stdlib.h>

void f1() {
  int* pa = NULL;
  printf("%d\n", (*pa));
}

void f2() {
  int* a = (int*)malloc(sizeof(int));
}

void f3() {
  int* a = (int*)malloc(100 * sizeof(int));
  a[100] = 0;
  free(a);
}

void f4() {
  int* a = (int*)malloc(3 * sizeof(int));
  a[0] = 10086;
  free(a);
  printf("%d\n", a[0]);
}

void f5() {
  int a = 10;
  int* pa = &a;
  free(pa);
}

// reference: http://www.cplusplus.com/reference/cstdlib/realloc/
void f6() {
  int* vec = NULL;
  int* next = NULL;
  int input;
  int count = 0;
  do {
    printf("Enter number (0 to end): ");
    scanf("%d", &input);
    count++;

    next = realloc(vec, count * sizeof(int));
    if (next != NULL) {
      vec = next;
      vec[count - 1] = input;
    } else {
      free(vec);
      free(next);
      fprintf(stderr, "Error (re)allocating memory");
      exit(1);
    }
  } while (input != 0);
  printf("Numbers entered: ");
  for (int i = 0; i < count; i++) {
    printf("%d, ", vec[i]);
  }
  printf("\n");
  free(vec);
  free(next);
}

int main() {
  f6();
}
