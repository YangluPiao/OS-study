#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sstream>

using namespace std;


void p1() {
  int x = 100;
  int rc = fork();
  if (rc < 0) {
    cerr << "fork failed" << endl;
    exit(1);
  } else if (rc == 0) {
    cout << "before child: " << x << endl; // this prints "100"
    x = 200;
    cout << "after child: " << x << endl;  // this prints "200"
  } else {
    int rc_wait = wait(NULL);
    cout << "before parent: " << x << endl; // this also prints "100"
    x = 300;
    cout << "after parent: " << x << endl;  // this prints "300"
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
  cout << c << endl;
  lseek(fd, 0, SEEK_SET);
  delete c;
}

void my_write(int fd, const char* content) {
  if (write(fd, content, 5) < 0) {
    cout << strerror(errno) << endl;
  }
}

void p2() {
  // The return value of open() is a file descriptor, a small, nonnegative
  // integer that is used in subsequent system calls
  int fd = open("test.txt", O_RDWR | O_APPEND); // content of file: "0123456789"
  cout << "file descriptor: " << fd << endl;
  int rc = fork();
  if (rc < 0) {
    cerr << "fork failed" << endl;
    exit(1);
  } else if (rc == 0) {
    // cout << "child read: ";
    // my_read(fd); // ok to access "fd", prints "01234"
    my_write(fd, "00000"); // appends "00000"
  } else {
    // int rc_wait = wait(NULL);
    // cout << "parent read: ";
    // my_read(fd); // also ok to access "fd", prints "56789"
    my_write(fd, "11111"); // appends "00000"
  }
}

void p4() {
  int rc = fork();
  if (rc < 0) {
    cerr << "fork failed" << endl;
    exit(1);
  } else if (rc == 0) {
    char* arr[2];
    arr[0] = strdup("/bin/ls");
    arr[1] = NULL;
    // execv(arr[0], arr);
    // execl(arr[0], arr[0], NULL);
    execle(arr[0], arr[0], NULL, NULL);
  }
}

void p5() {
  int rc = fork();
  if (rc < 0) {
    cerr << "fork failed" << endl;
    exit(1);
  } else if (rc == 0) {
    int rc_wait = wait(NULL); // returns -1
    cout << "child '" << getpid() << "' done, 'wait' returns: " << rc_wait << endl;
    cerr << "error: " << strerror(errno) << endl; // No child processes
  } else {
    int rc_wait = wait(NULL); // returns process ID of child process
    cout << "parent done: 'wait' returns: " << rc_wait << endl;
  }
}

void p6() {
  int rc = fork();
  if (rc < 0) {
    cerr << "fork failed" << endl;
    exit(1);
  } else if (rc == 0) {
    int rc_wait = waitpid(0, NULL, 0); // returns -1
    cout << "child '" << getpid() << "' done, 'waitpid' returns: " << rc_wait << endl;
    cerr << "error: " << strerror(errno) << endl; // No child processes
  } else {
    int rc_wait = waitpid(0, NULL, 0); // returns process ID of child process
    cout << "parent done: 'waitpid' returns: " << rc_wait << endl;
  }
}

void p7() {
  int rc = fork();
  if (rc < 0) {
    cerr << "fork failed" << endl;
    exit(1);
  } else if (rc == 0) {
    close(STDOUT_FILENO);
    cout << "123" << endl; // won't print
  }
}

void p8() {
  int pipe_fd[2];
  pipe(pipe_fd);
  cout << "read: " << pipe_fd[0] << " write: " << pipe_fd[1] << endl;
  int children[2]; // children[0] writes; children[1] reads
  children[0] = fork(); // forks the first child
  if (children[0] < 0) {
    cerr << "fork 0 failed" << endl;
    exit(1);
  } else if (children[0] == 0) {
    close(pipe_fd[0]); // close unused read end
    // generate a random string
    stringstream ss;
    for (int i = 0; i < 5; i++) {
      ss << (rand() % 10);
    }
    string tmp = ss.str();
    cout << getpid() << " writes: " << tmp << endl;
    write(pipe_fd[1], tmp.c_str(), 5);
    close(pipe_fd[1]); // finish writing, reader will see EOF
    waitpid(children[1], NULL, 0); // wait for reader, the second child
  } else {
    children[1] = fork(); // forks the second child
    if (children[1] < 0) {
      cerr << "fork 1 failed" << endl;
      exit(1);
    } else if (children[1] == 0) {
      close(pipe_fd[1]); // close unused write end
      cout << getpid() << " reads: ";
      my_read(pipe_fd[0]);
      close(pipe_fd[0]);
    }
  }
}

int main() {
  // p1();
  // p2();
  // p4();
  // p5();
  // p6();
  // p7();
  p8();
}
