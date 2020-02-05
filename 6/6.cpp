#include <iostream>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <sched.h>

using namespace std;

void my_sys_call() {
  int x = fork();
  switch (x) {
    case -1:
      cout << "failed to fork" << endl;
      exit(1);
    case 0:
      exit(0);
    default:
      (void)wait(NULL);
  }
}

void my_read(int fd) {
  // use calloc so that elements are initialized to '0'
  char* c = (char*) calloc(100, sizeof(char));
  int sz = read(fd, c, 5); // read 5 characters
  if (sz < 0) {
    cout << strerror(errno) << endl;
  }
  c[sz] = '\0';
  // cout << c << endl;
  lseek(fd, 0, SEEK_SET);
  delete c;
}

void my_lmbench() {
  int p1[2], p2[2];
  pipe(p1);
  pipe(p2);
  int child[2];
  child[0] = fork();

  cpu_set_t cpu_st;
  CPU_ZERO(&cpu_st);
  CPU_SET(0, &cpu_st); // set CPU to '0'
  switch (child[0]) {
    case -1:
      cout << "failed to fork" << endl;
      exit(1);
    case 0:
      // also set CPU to '0'
      if (sched_setaffinity(0, sizeof(cpu_st), &cpu_st) == -1)
        cerr << "error" << endl;
      write(p1[1], "12345", 5);
      my_read(p2[0]);
      exit(0);
    default:
      child[1] = fork();
      switch (child[1]) {
        case -1:
          cout << "failed to fork" << endl;
          exit(1);
        case 0:
          // again, set CPU to '0'
          if (sched_setaffinity(0, sizeof(cpu_st), &cpu_st) == -1)
            cerr << "error" << endl;
          write(p2[1], "54321", 5);
          my_read(p1[0]);
          exit(0);
      }
      (void)wait(NULL);
  }
}

template <typename T>
void measure(T (*fn)(), int times) {
  struct timeval t1, t2;
  gettimeofday(&t1, NULL);
  for (int i = 0; i < times; i++) {
    fn();
  }
  gettimeofday(&t2, NULL);
  double elapse = (t2.tv_sec - t1.tv_sec) * 1000.0;
  elapse += (t2.tv_usec - t1.tv_usec) / 1000.0;
  cout << "total: " << elapse << " ms" << endl;
  cout << "average: " << elapse / times << " ms" << endl;
}

int main() {
  measure(&my_sys_call, 10);
  measure(&my_lmbench, 10);
}
