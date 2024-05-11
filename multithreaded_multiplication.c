/*Q1) [ 20 points ] Write a multithreaded program that will multiply a three by
three matrix ( A ) with itself and put the result in another matrix (B). Each
thread will handle one “row” of A. The program should printout the resultant
matrix B.
*/

#include<stdio.h>
#include<pthread.h>

int A[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
int B[3][3];
int limit = 3;
pthread_mutex_t bmutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t bcond = PTHREAD_COND_INITIALIZER;
int row = 0;
int waitbarrier(void);
void *mm(void *param);
int main()
{
  pthread_t tid1,tid2,tid3;

  pthread_create(&tid1,NULL,mm,(void*)&row);

  pthread_create(&tid2,NULL,mm,(void*)&row);

  pthread_create(&tid3,NULL,mm,(void*)&row);

  pthread_join(tid1,NULL);
  pthread_join(tid2,NULL);
  pthread_join(tid3,NULL);
  
  //display resultant matrix
  for(int row=0;row<3;row++)
  {
     for(int col=0;col<3;col++){
       printf("%d ",B[row][col]);
     }
     printf("\n");
  }
  return 0;
}

void *mm(void *param)
{
  int myrow = *((int*)param);

  for(int i=0;i<3;i++)
  {
    int sum = 0;
    for(int j=0;j<3;j++)
     sum += A[myrow][j]*A[j][i];
    
    B[myrow][i] = sum;
  }
  waitbarrier();  
  pthread_exit(0);
}
int waitbarrier(void) // wait at the barrier until all n threads arrive
{
   int berror = 0;
   int error;

   if ( error = pthread_mutex_lock(&bmutex))  //couldn't lock, give up
      return error;
   row++;
   while ((row < limit) && !berror)
      berror = pthread_cond_wait(&bcond, &bmutex);
   if(!berror)
      berror = pthread_cond_broadcast(&bcond);  // wake up everyone
   error = pthread_mutex_unlock(&bmutex);

  if(berror)
      return berror;
  return error;
}
