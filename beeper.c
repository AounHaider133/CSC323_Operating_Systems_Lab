#include<stdio.h>
#include<sys/time.h>

int main(int argc,char* argv[])
{
  int sleeptime;
  if(argc != 2)
  {
    fprintf(stderr,"Usage:%s\n",argv[0]);
    return 1;
  }
  sleeptime = atoi(argv[1]);
  fprintf(stderr,"Sleep time is %d\n",sleeptime);
  for(;;)
  {
    sleep(sleeptime);
    printf("\007");
    fflush(stdout);
  }
}
