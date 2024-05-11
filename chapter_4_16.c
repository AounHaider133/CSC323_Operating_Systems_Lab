/* Write multithreaded program that will take a list of intergers as command line argument and create 3 threads t1 will compute average,
t2 will find maximum and t3 will find minimum */

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void *avg(void*);
void *max(void*);
void *min(void*);
int average;
int maximum = 0;
int minimum = 1111111111;
int main(int argc,char* argv[])
{
  if(argc == 1)
  {
    fprintf(stderr,"Pass the list of integers.\n");
    return 1;
  }
  
  pthread_t t1,t2,t3;
  pthread_create(&t1,NULL,avg,(void*)argv);
  pthread_create(&t2,NULL,max,(void*)argv);
  pthread_create(&t3,NULL,min,(void*)argv);
  pthread_join(t1,NULL);
  pthread_join(t2,NULL);
  pthread_join(t3,NULL);
  
  printf("Average is: %d\n",average);
  printf("Max is: %d\n",maximum);
  printf("Min is: %d\n",minimum);
  
  return 0;
}

void *avg(void* param)
{
  char **elem = (char**)param;
  int sum = 0;
  int len = 1;

  while(elem[len] != NULL){
   sum += atoi(elem[len]);
   len++;
  }

  average = sum/(len-1);
  pthread_exit(0);
}

void *max(void* param)
{
  char **elem = (char**)param;
  int len = 1;

  while(elem[len] != NULL){
   if(atoi(elem[len]) > maximum)
    maximum = atoi(elem[len]);
   len++;
  }
  
  pthread_exit(0);
}

void *min(void* param)
{
  char **elem = (char**)param;
  int len = 1;

  while(elem[len] != NULL){
   if(atoi(elem[len]) < minimum)
    minimum = atoi(elem[len]);
   len++;
  }
  
  pthread_exit(0);
}
