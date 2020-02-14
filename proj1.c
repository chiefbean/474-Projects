#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

int main()
{
  int fd1[2];
  int fd2[2];
  int pid;
  int n = 1;
  char *size = '1000';

  if (pipe(fd1)==-1)
  {
      fprintf(stderr, "Pipe Failed" );
      return 1;
  }
  if (pipe(fd2)==-1)
  {
      fprintf(stderr, "Pipe Failed" );
      return 1;
  }

  pid = fork();

  // for(int i = 0; i < n-1; i++) {
  //   if (pid > 0) {
  //     pid = fork();
  //   }
  // }
  if (pid > 0) {
    char *returnValue;
    float hyTan;
    close(fd1[0]);

    write(fd1[1], size, 4);
    close(fd1[1]);

    wait(NULL);

    close(fd2[1]);

    read(fd2[0], returnValue, 6);

    sscanf(returnValue, "%6f", &hyTan);

    printf("Hyperbolic Tan  %6f\n", hyTan);
    close(fd2[0]);
  }

  if(pid == 0) {
    close(fd1[1]);
    char *returnValue;
    int m;
    read(fd1[0], returnValue, 4);

    sscanf(returnValue, "%10d", m);

    double x;
    double sum = 0;
    char *output;

    for(int i = 0; i < m; i++) {
      x = (double)i / (double)m;
      sum += tanh(x);
      //printf("%6f\n", sum);
    }

    sprintf(output, "%6f", sum);
    printf("%6f: %6s\n", sum, output);

    close(fd1[0]);
    close(fd2[0]);

    write(fd2[1], output, 6);
    close(fd2[1]);

    exit(0);
  }
}
