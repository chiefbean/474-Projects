// ***********************************************
// *                                             *
// *            CSCI 474 Project 2               *
// * Steven Karschnia, Keon Woo Kim, Ryan Peters *
// *                                             *
// ***********************************************
#include <stdio.h>

int fifo(int frames, int pages, int read[])
{
    int page_faults = 0;
    int temp[frames];
    for(int i = 0; i < frames; i++)
    {
        temp[i] = -1;
    }
    for(int i = 0; i < pages; i++)
    {
        int s = 0;
        for(int j = 0; j < frames; j++)
        {
            if(read[i] == temp[j])
            {
                s++;
                page_faults--;
            }
        }
        page_faults++;
        if((page_faults <= frames) && (s == 0))
        {
            temp[i] = read[i];
        }
        else if(s == 0)
        {
            temp[(page_faults - 1) % frames] = read[i];
        }
    }
    return page_faults;
}

int lru(int total_frames, int total_pages, int pages[])
{
    char buff[255];

    int temp[total_pages], frames[total_frames];
    int m, n, position, k, l;
    int a = 0, b = 0, page_fault = 0;
    for(m = 0; m < total_frames; m++)
    {
        frames[m] = -1;
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
    }
    return page_fault;
}

int clock(int frames, int pages, int read[])
{
    int temp[frames], use[frames], page_faults, locat, found;
    for(int i = 0; i < frames; i++)
    {
        temp[i] = -1;
        use[i] = 0;
    }
    page_faults = 0;
    locat = 0;
    for(int i = 0; i < pages; i++)
    {
        found = 0;
        for(int j = 0; j < frames; j++)
        {
            if(temp[j] == read[i])
            {
                use[j] = 1;
                found = 1;
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
                    page_faults++;
                    found = 1;
                }
                else
                {
                    use[locat] = 0;
                }
                locat++;
                if(locat == frames)
                    locat = 0;
            } while(found != 1);
        }
        printf("\n");
    }
    page_faults -= frames;
    return page_faults;
}

int optimal(int frames, int pages, int read[])
{
    int temp[frames], interval[frames];
    int page_faults, flag, found, position, maxInterval, prev = -1;
    for(int i = 0; i < frames; i++)
    {
        temp[i] = -1;
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
    }
    page_faults -= frames;
    return page_faults;
}

int main(int argc, char** argv)
{
    FILE *fp;
    char buff[255];

    //read in command line arguments
    char *fileName = argv[1];
    int minFrames = atoi(argv[2]);
    int maxFrames = atoi(argv[3]);
    int pages = atoi(argv[4]);
    int read[pages];

    fp = fopen(fileName, "r");

    for(int i = 0; i < pages; i++)
    {
        fscanf(fp, "%s", buff);
        read[i] = atoi(buff);
    }

    int fifoFaults = fifo(maxFrames, pages, read);

    int lruFaults = lru(maxFrames, pages, read);

    int clockFaults = clock(maxFrames, pages, read);

    int optFaults = optimal(maxFrames, pages, read);

    fclose(fp);

    printf("+ FIFO +----------------------+");
    printf("| Total page faults: %d       |", fifoFaults);
    printf("+-----------------------------+");
}
