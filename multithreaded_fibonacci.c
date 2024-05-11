/* Write a multithreaded program which will create a thread which will generate fibonacci series and store it in a list less than n */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<pthread.h>

int *x;
void* fib(void*);
void* display_lst(int*,int);
int main(int argc,char* argv[])
{
  if(argc < 2)
  {
    printf("Usage:%s\n",argv[0]);
    return 1;
  }
  
  x = (int*)malloc((argc-1)*sizeof(int));
  pthread_t t1;
  
  pthread_create(&t1,NULL,fib,(void*)argv[1]);

  pthread_join(t1,NULL);
  
  display_lst(x,atoi(argv[1]));
  free(x);
  return 0;
}

void* display_lst(int* lst,int len)
{
  for (int i = 0; i < len; i++)
     printf("%d ",lst[i]);
  
  printf("\n");
}

void* fib(void* param)
{
  int n = *((int*)param);
  x[0] = 0;
  x[1] = 1;
  
  for(int i=2;x[i-1]+x[i-2]<n;i++)
   x[i] = x[i-1]+x[i-2];
  
  pthread_exit(0);
}
