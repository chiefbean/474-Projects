#include <stdio.h>

void fifo(FILE fp)
{

}

int main(int argc, char** argv)
{
    FILE *fp;
    char buff[255];

    char *fileName = argv[1];
    int minFrames = argv[2];
    int maxFrames = argv[3];
    int pages = argv[4];

    fp = fopen(fileName, "r");
    fifo(fp);
    fclose(fp);
}
