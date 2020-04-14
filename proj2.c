// ***********************************************
// *                                             *
// *            CSCI 474 Project 2               *
// * Steven Karschnia, Keon Woo Kim, Ryan Peters *
// *                                             *
// ***********************************************
#include <stdio.h>

void fifo(char *fileName, int frames, int pages)
{
    int page_faults = 0, read;
    FILE *fp = fopen(fileName, "r");
    char buff[255];

    int temp[frames];
    for(int i = 0; i < frames; i++)
    {
        temp[i] = -1;
    }
    for(int i = 0; i < pages; i++)
    {
        int s = 0;
        fscanf(fp, "%s", buff);
        read = atoi(buff);
        for(int j = 0; j < frames; j++)
        {
            if(read == temp[j])
            {
                s++;
                page_faults--;
            }
        }
        page_faults++;
        if((page_faults <= frames) && (s == 0))
        {
            temp[i] = read;
        }
        else if(s == 0)
        {
            temp[(page_faults - 1) % frames] = read;
        }
        printf("\n");
        for(int j = 0; j < frames; j++)
        {
            printf("%d\t", temp[j]);
        }
    }
    printf("\ntotal page faults: %d\n", page_faults);
    fclose(fp);
}

int main(int argc, char** argv)
{
    FILE *fp;

    //read in command line arguments
    char *fileName = argv[1];
    int minFrames = atoi(argv[2]);
    int maxFrames = atoi(argv[3]);
    int pages = atoi(argv[4]);

    printf("FIFO \n");
    fifo(fileName, maxFrames, pages);
}
