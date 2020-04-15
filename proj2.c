// ***********************************************
// *                                             *
// *            CSCI 474 Project 2               *
// * Steven Karschnia, Keon Woo Kim, Ryan Peters *
// *                                             *
// ***********************************************
#include <stdio.h>

void fifo(FILE *fp, int frames, int pages)
{
    int page_faults = 0, read;
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
    page_faults -= frames;
    printf("\ntotal page faults: %d\n", page_faults);
}

void lru(FILE *fp, int frameSize, int total_pages)
{
    int page_faults = 0, position;
    char buff[255];

    int temp[total_pages], frames[frameSize], pages[total_pages],;
    int total_pages, m, n, position, k, l, total_frames;
    int a = 0, b = 0, page_fault = 0;
    for(m = 0; m < total_frames; m++)
    {
        frames[m] = -1;
    }
    for(m = 0; m < total_pages; m++)
    {
        fscanf(fp, "%s", buff);
        pages[i] = atoi(buff);
    }
    for(n = 0; n < total_pages; n++)
    {
        a = 0, b = 0;
        for(m = 0; m < total_frames; m++)
        {
            if(frames[m] == pages[n])
            {
                a = 1;
                b = 1;
                break;
            }
        }
        if(a == 0)
        {
            for(m = 0; m < total_frames; m++)
            {
                if(frames[m] == -1)
                {
                    frames[m] = pages[n];
                    b = 1;
                    break;
                }
            }
        }
        if(b == 0)
        {
            for(m = 0; m < total_frames; m++)
            {
                temp[m] = 0;
            }
            for(k = n - 1, l = 1; l <= total_frames - 1; l++, k--)
            {
                for(m = 0; m < total_frames; m++)
                {
                    if(frames[m] == pages[k])
                    {
                        temp[m] = 1;
                    }
                }
            }
            for(m = 0; m < total_frames; m++)
            {
                if(temp[m] == 0)
                    position = m;
            }
            frames[position] = pages[n];
            page_fault++;
        }
        printf("\n");
        for(m = 0; m < total_frames; m++)
        {
            printf("%d\t", frames[m]);
        }
    }
    printf("\nTotal Number of Page Faults:\t%d\n", page_fault);
}

void clock(FILE *fp, int frames, int pages)
{
    int temp[frames], use[frames], read[pages], page_faults, locat, found;
    char buff[255];
    for(int i = 0; i < frames; i++)
    {
        temp[i] = -1;
        use[i] = 0;
    }
    for(int i = 0; i < pages; i++)
    {
        fscanf(fp, "%s", buff);
        read[i] = atoi(buff);
    }
    page_faults = 0;
    locat = 0;
    for(int i = 0; i < pages; i++)
    {
        found = 0;
        for(int j = 0; j < frames; j++)
        {
            if(read[i] == temp[j])
            {
                found = 1;
                use[j] = 1;
                break;
            }
        }
        if(found == 0)
        {
            do {
                if(use[locat] == 0)
                {
                    temp[locat] = read[i];
                    use[locat] = 1;
                    found = 1;
                    page_faults++;
                } else {
                  use[locat] = 0;
                }
                locat++;
                if(locat == i)
                    locat = 0;
            } while(found != 1);
        }
        printf("\n");
        for(int j = 0; j < frames; j++)
        {
            printf("%d\t", temp[j]);
        }
    }
    page_faults -= frames;
    printf("\ntotal page faults: %d\n", page_faults);
}

void optimal(FILE *fp, int frames, int pages)
{
    int temp[frames], read[pages], interval[frames];
    int page_faults, flag, found, position, maxInterval, prev = -1;
    char buff[255];
    for(int i = 0; i < frames; i++)
    {
        temp[i] = -1;
    }
    for(int i = 0; i < pages; i++)
    {
        fscanf(fp, "%s", buff);
        read[i] = atoi(buff);
    }
    page_faults = 0;
    for(int i = 0; i < pages; i++)
    {
        flag = 0;
        for(int j = 0; j < frames; j++)
        {
            if(temp[j] == read[i])
            {
                flag = 1;
                break;
            }
        }
        if(flag == 0)
        {
            if(prev == frames - 1)
            {
                for(int j = 0; j < frames; j++)
                {
                    for(int k = i + 1; k < pages; k++)
                    {
                        interval[j] = 0;
                        if(temp[j] == read[k])
                        {
                            interval[j] = k - i;
                            break;
                        }
                    }
                }
                found = 0;
                for(int j = 0; j < frames; j++)
                {
                    if(interval[j] == 0)
                    {
                        position = j;
                        found = 1;
                        break;
                    }
                }
            }
            else
            {
                position = ++prev;
                found = 1;
            }
            if(found == 0)
            {
                maxInterval = interval[0];
                position = 0;
                for(int j = 0; j < frames; j++)
                {
                    if(maxInterval < interval[j])
                    {
                        maxInterval = interval[j];
                        position = j;
                    }
                }
            }
            temp[position] = read[i];
            page_faults++;
        }
        printf("\n");
        for(int j = 0; j < frames; j++)
        {
            printf("%d\t", temp[j]);
        }
    }
    page_faults -= frames;
    printf("\ntotal page faults: %d\n", page_faults);
}

int main(int argc, char** argv)
{
    FILE *fp;

    //read in command line arguments
    char *fileName = argv[1];
    int minFrames = atoi(argv[2]);
    int maxFrames = atoi(argv[3]);
    int pages = atoi(argv[4]);

    fp = fopen(fileName, "r");

    //printf("FIFO \n");
    //fifo(fp, maxFrames, pages);

    //printf("\nLRU \n");
    lru(fp, maxFrames, pages);

    //printf("\nClock \n");
    //clock(fp, maxFrames, pages);

    //printf("\nOptimal \n");
    //optimal(fp, maxFrames, pages);

    fclose(fp);
}
