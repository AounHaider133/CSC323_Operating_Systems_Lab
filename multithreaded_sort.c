/* Write a multithreading sorting program which will sort two segments of array and then merge them */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<pthread.h>

typedef struct {
 int start;
 int end;
}ThreadParams;

void *sort(void*);
void* display_lst();

int lst[] = {7,12,19,3,18,4,2,6,15,8};

int main(int argc,char* argv[])
{

  int len = sizeof(lst)/sizeof(int);
  int mid = len/2;
  pthread_t t1,t2,t3;

  ThreadParams param1 = {0,mid-1};
  ThreadParams param2 = {mid,len-1};  

  printf("Orignal list is:");
  display_lst(len);
    
  pthread_create(&t1,NULL,sort,&param1);
  pthread_create(&t2,NULL,sort,&param2);  

  pthread_join(t1,NULL);
  pthread_join(t2,NULL);  

  printf("Sort list is:   ");
  display_lst(len);
  return 0;
}

void* display_lst(int len)
{
  for (int i = 0; i < len; i++)
     printf("%d ",lst[i]);
  
  printf("\n");
}
void* sort(void* param)
{
  ThreadParams p = *(ThreadParams*)param;
  int start = p.start;
  int end = p.end;
  
  int temp;
  for (int i = start; i < end - 1; i++) {
        for (int j = start; j < end - i; j++) {
            if (lst[j] > lst[j + 1]) {
                // Swap lst[j] and lst[j+1]
                temp = lst[j];
                lst[j] = lst[j + 1];
                lst[j + 1] = temp;
            }
        }
    }
    
  pthread_exit(0);
}
