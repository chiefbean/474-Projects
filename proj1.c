#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <signal.h>

void oneProc(double size)
{
  clock_t before = clock();
  time_t start = time(NULL);
  int pipeArray[2][2];

  pipe(pipeArray[0]);
  pipe(pipeArray[1]);

  if(fork() == 0) {
    close(pipeArray[0][1]);
    double m;
    read(pipeArray[0][0], &m, sizeof(m));

    long double x;
    long double sum = 0;

    for(int i = 0; i <= m; i++) {
      x = (double)i / (double)m;
      sum += tanh(x);
    }
    close(pipeArray[0][0]);
    close(pipeArray[1][0]);

    write(pipeArray[1][1], &sum, sizeof(sum));
    close(pipeArray[1][1]);

    clock_t difference = clock() - before;
    long int msec = difference * 1000 / CLOCKS_PER_SEC;
    printf("Time taken by one process: %6ld msec\n", msec);

    time_t diff = time(NULL) - start;
    printf("Wall clock time taken by one process: %6ld sec\n", diff);

    kill(getpid(), SIGTERM);
  } else {
    long double hyTan;
    close(pipeArray[0][0]);

    write(pipeArray[0][1], &size, sizeof(size));
    close(pipeArray[0][1]);

    wait(NULL);

    close(pipeArray[1][1]);

    read(pipeArray[1][0], &hyTan, sizeof(hyTan));

    printf("Hyperbolic Tangent, One Process: %6Lf\n\n", hyTan);

    close(pipeArray[1][0]);
  }
}

void twoProc(double size)
{
  clock_t before = clock();
  time_t start = time(NULL);
  int pipeArray[4][2];

  pipe(pipeArray[0]);
  pipe(pipeArray[1]);
  pipe(pipeArray[2]);
  pipe(pipeArray[3]);

  if(fork() == 0) {
    close(pipeArray[0][1]);
    double m;
    read(pipeArray[0][0], &m, sizeof(m));

    long double x;
    long double sum = 0;

    for(int i = 0; i < m/2; i++) {
      x = (double)i / (double)m;
      sum += tanh(x);
    }
    close(pipeArray[0][0]);
    close(pipeArray[1][0]);

    write(pipeArray[1][1], &sum, sizeof(sum));
    close(pipeArray[1][1]);

    kill(getpid(), SIGTERM);
  } else if (fork() == 0) {
    close(pipeArray[2][1]);
    double m;
    read(pipeArray[2][0], &m, sizeof(m));

    long double x;
    long double sum = 0;

    for(int i = m; i >= m/2; i--) {
      x = (double)i / (double)m;
      sum += tanh(x);
    }
    close(pipeArray[2][0]);
    close(pipeArray[3][0]);

    write(pipeArray[3][1], &sum, sizeof(sum));
    close(pipeArray[3][1]);

    clock_t difference = clock() - before;
    long int msec = difference * 1000 / CLOCKS_PER_SEC;
    printf("Time taken by two processes: %6ld msec\n", msec);

    time_t diff = time(NULL) - start;
    printf("Wall clock time taken by two processes: %6ld sec\n", diff);

    kill(getpid(), SIGTERM);
  } else {
    long double child1;
    long double child2;
    long double hyTan;

    close(pipeArray[0][0]);
    write(pipeArray[0][1], &size, sizeof(size));
    close(pipeArray[0][1]);

    wait(NULL);

    close(pipeArray[1][1]);
    read(pipeArray[1][0], &child1, sizeof(child1));
    close(pipeArray[1][0]);

    write(pipeArray[2][1], &size, sizeof(size));
    close(pipeArray[2][1]);

    wait(NULL);

    close(pipeArray[3][1]);
    read(pipeArray[3][0], &child2, sizeof(child2));

    hyTan = child1 + child2;

    printf("Hyperbolic Tangent, Two Processes: %6Lf\n\n", hyTan);
    close(pipeArray[3][0]);
  }
}

void fourProc(double size)
{
  clock_t before = clock();
  time_t start = time(NULL);
  int pipeArray[8][2];

  pipe(pipeArray[0]);
  pipe(pipeArray[1]);
  pipe(pipeArray[2]);
  pipe(pipeArray[3]);
  pipe(pipeArray[4]);
  pipe(pipeArray[5]);
  pipe(pipeArray[6]);
  pipe(pipeArray[7]);

  if(fork() == 0) {
    close(pipeArray[0][1]);
    double m;
    read(pipeArray[0][0], &m, sizeof(m));

    long double x;
    long double sum = 0;

    for(int i = 0; i < m/4; i++) {
      x = (double)i / (double)m;
      sum += tanh(x);
    }
    close(pipeArray[0][0]);
    close(pipeArray[1][0]);

    write(pipeArray[1][1], &sum, sizeof(sum));
    close(pipeArray[1][1]);

    kill(getpid(), SIGTERM);
  } else if (fork() == 0) {
    close(pipeArray[2][1]);
    double m;
    read(pipeArray[2][0], &m, sizeof(m));

    long double x;
    long double sum = 0;

    for(int i = m/4; i < m/2; i++) {
      x = (double)i / (double)m;
      sum += tanh(x);
    }
    close(pipeArray[2][0]);
    close(pipeArray[3][0]);

    write(pipeArray[3][1], &sum, sizeof(sum));
    close(pipeArray[3][1]);

    kill(getpid(), SIGTERM);
  } else if (fork() == 0) {
    close(pipeArray[4][1]);
    double m;
    read(pipeArray[4][0], &m, sizeof(m));

    long double x;
    long double sum = 0;

    for(int i = m/2; i < 3*(m/4); i++) {
      x = (double)i / (double)m;
      sum += tanh(x);
    }
    close(pipeArray[4][0]);
    close(pipeArray[5][0]);

    write(pipeArray[5][1], &sum, sizeof(sum));
    close(pipeArray[5][1]);

    kill(getpid(), SIGTERM);
  } else if (fork() == 0) {
    close(pipeArray[6][1]);
    double m;
    read(pipeArray[6][0], &m, sizeof(m));

    long double x;
    long double sum = 0;

    for(int i = 3*(m/4); i <= m; i++) {
      x = (double)i / (double)m;
      sum += tanh(x);
    }
    close(pipeArray[6][0]);
    close(pipeArray[7][0]);

    write(pipeArray[7][1], &sum, sizeof(sum));
    close(pipeArray[7][1]);

    clock_t difference = clock() - before;
    long int msec = difference * 1000 / CLOCKS_PER_SEC;
    printf("Time taken by four processes: %6ld msec\n", msec);

    time_t diff = time(NULL) - start;
    printf("Wall clock time taken by four processes: %6ld sec\n", diff);

    kill(getpid(), SIGTERM);
  } else {
    long double child1;
    long double child2;
    long double child3;
    long double child4;
    long double hyTan;

    close(pipeArray[0][0]);
    write(pipeArray[0][1], &size, sizeof(size));
    close(pipeArray[0][1]);

    wait(NULL);

    close(pipeArray[1][1]);
    read(pipeArray[1][0], &child1, sizeof(child1));
    close(pipeArray[1][0]);

    write(pipeArray[2][1], &size, sizeof(size));
    close(pipeArray[2][1]);

    wait(NULL);

    close(pipeArray[3][1]);
    read(pipeArray[3][0], &child2, sizeof(child2));
    close(pipeArray[3][0]);

    close(pipeArray[4][0]);
    write(pipeArray[4][1], &size, sizeof(size));
    close(pipeArray[4][1]);

    wait(NULL);

    close(pipeArray[5][1]);
    read(pipeArray[5][0], &child3, sizeof(child3));
    close(pipeArray[5][0]);

    close(pipeArray[6][0]);
    write(pipeArray[6][1], &size, sizeof(size));
    close(pipeArray[6][1]);

    wait(NULL);

    close(pipeArray[7][1]);
    read(pipeArray[7][0], &child4, sizeof(child4));
    close(pipeArray[7][0]);

    hyTan = child1 + child2 + child3 + child4;

    printf("Hyperbolic Tangent, Four Processes: %6Lf\n\n", hyTan);
  }
}

void eightProc(double size)
{
  clock_t before = clock();
  time_t start = time(NULL);
  int pipeArray[16][2];

  pipe(pipeArray[0]);
  pipe(pipeArray[1]);
  pipe(pipeArray[2]);
  pipe(pipeArray[3]);
  pipe(pipeArray[4]);
  pipe(pipeArray[5]);
  pipe(pipeArray[6]);
  pipe(pipeArray[7]);
  pipe(pipeArray[8]);
  pipe(pipeArray[9]);
  pipe(pipeArray[10]);
  pipe(pipeArray[11]);
  pipe(pipeArray[12]);
  pipe(pipeArray[13]);
  pipe(pipeArray[14]);
  pipe(pipeArray[15]);

  if(fork() == 0) {
    close(pipeArray[0][1]);
    double m;
    read(pipeArray[0][0], &m, sizeof(m));

    long double x;
    long double sum = 0;

    for(int i = 0; i < m/8; i++) {
      x = (double)i / (double)m;
      sum += tanh(x);
    }
    close(pipeArray[0][0]);
    close(pipeArray[1][0]);

    write(pipeArray[1][1], &sum, sizeof(sum));
    close(pipeArray[1][1]);

    kill(getpid(), SIGTERM);
  } else if (fork() == 0) {
    close(pipeArray[2][1]);
    double m;
    read(pipeArray[2][0], &m, sizeof(m));

    long double x;
    long double sum = 0;

    for(int i = m/8; i < m/4; i++) {
      x = (double)i / (double)m;
      sum += tanh(x);
    }
    close(pipeArray[2][0]);
    close(pipeArray[3][0]);

    write(pipeArray[3][1], &sum, sizeof(sum));
    close(pipeArray[3][1]);

    kill(getpid(), SIGTERM);
  } else if (fork() == 0) {
    close(pipeArray[4][1]);
    double m;
    read(pipeArray[4][0], &m, sizeof(m));

    long double x;
    long double sum = 0;

    for(int i = m/4; i < 3*(m/8); i++) {
      x = (double)i / (double)m;
      sum += tanh(x);
    }
    close(pipeArray[4][0]);
    close(pipeArray[5][0]);

    write(pipeArray[5][1], &sum, sizeof(sum));
    close(pipeArray[5][1]);

    kill(getpid(), SIGTERM);
  } else if (fork() == 0) {
    close(pipeArray[6][1]);
    double m;
    read(pipeArray[6][0], &m, sizeof(m));

    long double x;
    long double sum = 0;

    for(int i = 3*(m/8); i < m/2; i++) {
      x = (double)i / (double)m;
      sum += tanh(x);
    }
    close(pipeArray[6][0]);
    close(pipeArray[7][0]);

    write(pipeArray[7][1], &sum, sizeof(sum));
    close(pipeArray[7][1]);

    kill(getpid(), SIGTERM);
  } else if (fork() == 0) {
    close(pipeArray[8][1]);
    double m;
    read(pipeArray[8][0], &m, sizeof(m));

    long double x;
    long double sum = 0;

    for(int i = m/2; i < 5*m/8; i++) {
      x = (double)i / (double)m;
      sum += tanh(x);
    }
    close(pipeArray[8][0]);
    close(pipeArray[9][0]);

    write(pipeArray[9][1], &sum, sizeof(sum));
    close(pipeArray[9][1]);

    kill(getpid(), SIGTERM);
  } else if (fork() == 0) {
    close(pipeArray[10][1]);
    double m;
    read(pipeArray[10][0], &m, sizeof(m));

    long double x;
    long double sum = 0;

    for(int i = 5*m/8; i < 3*m/4; i++) {
      x = (double)i / (double)m;
      sum += tanh(x);
    }
    close(pipeArray[10][0]);
    close(pipeArray[11][0]);

    write(pipeArray[11][1], &sum, sizeof(sum));
    close(pipeArray[11][1]);

    kill(getpid(), SIGTERM);
  } else if (fork() == 0) {
    close(pipeArray[12][1]);
    double m;
    read(pipeArray[12][0], &m, sizeof(m));

    long double x;
    long double sum = 0;

    for(int i = 3*(m/4); i < 7*m/8; i++) {
      x = (double)i / (double)m;
      sum += tanh(x);
    }
    close(pipeArray[12][0]);
    close(pipeArray[13][0]);

    write(pipeArray[13][1], &sum, sizeof(sum));
    close(pipeArray[13][1]);

    kill(getpid(), SIGTERM);
  } else if (fork() == 0) {
    close(pipeArray[14][1]);
    double m;
    read(pipeArray[14][0], &m, sizeof(m));

    long double x;
    long double sum = 0;

    for(int i = 7*(m/8); i <= m; i++) {
      x = (double)i / (double)m;
      sum += tanh(x);
    }
    close(pipeArray[14][0]);
    close(pipeArray[15][0]);

    write(pipeArray[15][1], &sum, sizeof(sum));
    close(pipeArray[15][1]);

    clock_t difference = clock() - before;
    long int msec = difference * 1000 / CLOCKS_PER_SEC;
    printf("Time taken by eight processes: %6ld msec\n", msec);

    time_t diff = time(NULL) - start;
    printf("Wall clock time taken by eight processes: %6ld sec\n", diff);

    kill(getpid(), SIGTERM);
  } else {
    long double child1;
    long double child2;
    long double child3;
    long double child4;
    long double child5;
    long double child6;
    long double child7;
    long double child8;
    long double hyTan;

    close(pipeArray[0][0]);
    write(pipeArray[0][1], &size, sizeof(size));
    close(pipeArray[0][1]);

    wait(NULL);

    close(pipeArray[1][1]);
    read(pipeArray[1][0], &child1, sizeof(child1));
    close(pipeArray[1][0]);

    write(pipeArray[2][1], &size, sizeof(size));
    close(pipeArray[2][1]);

    wait(NULL);

    close(pipeArray[3][1]);
    read(pipeArray[3][0], &child2, sizeof(child2));
    close(pipeArray[3][0]);

    close(pipeArray[4][0]);
    write(pipeArray[4][1], &size, sizeof(size));
    close(pipeArray[4][1]);

    wait(NULL);

    close(pipeArray[5][1]);
    read(pipeArray[5][0], &child3, sizeof(child3));
    close(pipeArray[5][0]);

    close(pipeArray[6][0]);
    write(pipeArray[6][1], &size, sizeof(size));
    close(pipeArray[6][1]);

    wait(NULL);

    close(pipeArray[7][1]);
    read(pipeArray[7][0], &child4, sizeof(child4));
    close(pipeArray[7][0]);

    close(pipeArray[8][0]);
    write(pipeArray[8][1], &size, sizeof(size));
    close(pipeArray[8][1]);

    wait(NULL);

    close(pipeArray[9][1]);
    read(pipeArray[9][0], &child5, sizeof(child5));
    close(pipeArray[9][0]);

    write(pipeArray[10][1], &size, sizeof(size));
    close(pipeArray[10][1]);

    wait(NULL);

    close(pipeArray[11][1]);
    read(pipeArray[11][0], &child6, sizeof(child6));
    close(pipeArray[11][0]);

    close(pipeArray[12][0]);
    write(pipeArray[12][1], &size, sizeof(size));
    close(pipeArray[12][1]);

    wait(NULL);

    close(pipeArray[13][1]);
    read(pipeArray[13][0], &child7, sizeof(child7));
    close(pipeArray[13][0]);

    close(pipeArray[14][0]);
    write(pipeArray[14][1], &size, sizeof(size));
    close(pipeArray[14][1]);

    wait(NULL);

    close(pipeArray[15][1]);
    read(pipeArray[15][0], &child8, sizeof(child8));
    close(pipeArray[15][0]);

    hyTan = child1 + child2 + child3 + child4 + child5 + child6 + child7 + child8;

    printf("Hyperbolic Tangent, Eight Processes: %6Lf\n\n", hyTan);
  }
}

int main()
{
  // printf("One Child:\n");
  // printf("Small size (100,000,000)\n");
  // oneProc(100000000);
  // printf("Medium size (1,000,000,000)\n");
  // oneProc(1000000000);
  // printf("Large size (10,000,000,000)\n");
  // oneProc(10000000000);
  //
  // printf("Two Children:\n");
  // printf("Small size (100,000,000)\n");
  // twoProc(100000000);
  // printf("Medium size (1,000,000,000)\n");
  // twoProc(1000000000);
  // printf("Large size (10,000,000,000)\n");
  // twoProc(10000000000);
  //
  // printf("Four Children:\n");
  // printf("Small size (100,000,000)\n");
  // fourProc(100000000);
  // printf("Medium size (1,000,000,000)\n");
  // fourProc(1000000000);
  // printf("Large size (10,000,000,000)\n");
  // fourProc(10000000000);

  printf("Eight Children:\n");
  printf("Small size (100,000,000)\n");
  eightProc(100000000);
  printf("Medium size (1,000,000,000)\n");
  eightProc(1000000000);
  printf("Large size (10,000,000,000)\n");
  eightProc(10000000000);

}
