#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
int main()
{
    struct timeval start, end;
 
    unsigned long mtime, seconds, useconds;    
 
    gettimeofday(&start, NULL);
//    usleep(20);
    gettimeofday(&end, NULL);
 
    seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;
 
    mtime = useconds;
 
    printf("Elapsed time: %ld microsecons\n", mtime);
 
    return 0;
}
