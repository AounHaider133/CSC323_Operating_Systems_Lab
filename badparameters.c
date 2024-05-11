#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#define NUMTHREADS 10

void *runner(void *param);
int main()
{
  pthread_t tid[NUMTHREADS];
  int errno,i,j;
  
  for(i=0; i<NUMTHREADS; i++)
   if(errno = pthread_create(tid+1,NULL,runner,(void*)&i)){
      fprintf(stderr,"Failed to create thread: %s",strerror(errno));
      tid[i] = pthread_self();
   }
  
  for(j=0; j<NUMTHREADS; j++)
   if(pthread_equal(tid[j],pthread_self()))
    continue;
   if(errno = pthread_join(tid[j],NULL))
    fprintf(stderr,"Failed to join thread: %s\n",strerror(errno));
  
  printf("All threads done.\n");
  return 0;
}
void *runner(void *param)
{
  sleep(1);
  fprintf(stderr,"Thread received %d\n",*(int*)param);
  return NULL;
}
