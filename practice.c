#include<stdio.h>
#include<errno.h>
#include<pthread.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t bcond = PTHREAD_COND_INITIALIZER;
int A[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
int B[3][3];
int count = 0,limit = 3;

void *fun(void *param);
void waitbarrier();

int main()
{
  pthread_t t1,t2,t3;
  pthread_attr_t a1,a2,a3;

  pthread_attr_init(&a1);
  pthread_attr_init(&a2);
  pthread_attr_init(&a3);

  pthread_create(&t1,&a1,fun,(void*)&count);
  pthread_create(&t2,&a2,fun,(void*)&count);
  pthread_create(&t3,&a3,fun,(void*)&count);

  pthread_join(t1,NULL);
  pthread_join(t2,NULL);
  pthread_join(t3,NULL);

  //print the result
  int i,j;
  for(i = 0; i < 3; i++)
  {
    for(j = 0;j < 3;j++){
      printf("%d ",B[i][j]);
    }
    printf("\n");
  }
  return 0;

}

void *fun(void *param)
{
  int row = *((int*)param);
  int sum = 0;
  int i,j;
  for(i = 0; i < 3; i++)
  {
    sum = 0;
    for(j = 0;j < 3;j++)
     sum += A[row][j]*A[j][i];
    B[row][i] = sum;
  }
    waitbarrier();
}

void waitbarrier()
{
  pthread_mutex_lock(&lock);
  count++;
  while(count<limit)
   pthread_cond_wait(&bcond,&lock);

  pthread_cond_broadcast(&bcond);

  pthread_mutex_unlock(&lock);
}
