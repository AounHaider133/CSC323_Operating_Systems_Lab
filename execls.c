#include<stdio.h>
#include<semaphore.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

#define NUM_OF_PHILOSOPHER 5
#define SEMKEY 133

sem_t chopsticks[NUM_OF_PHILOSOPHER];
pthread_t philosopher[NUM_OF_PHILOSOPHER];
int sem_id;

void *runner(void* param){
 int philosopher_id = *((int*)param);
 srand(time(NULL));
 
 printf("philosopher # %d wants to eat\n",philosopher_id);
 
 chopsticks_op(philosopher_id,-1);
 printf("philosopher # %d going to eat\n",philosopher_id);
 sleep(rand()%3+1);
 
 chopsticks_op(philosopher_id,1);
 printf("philosopher # %d done eating, now going to think\n",philosopher_id);
 sleep(rand()%3+1);
 
}

void chopsticks_op(int philosopher_id,int status)
{  
  struct sembuf[2] op;
  int left_chopstick = philosopher_id;
  int right_chopstick = (philosopher_id+1)%NUM_OF_PHILOSOPHER;

  op[0].sem_num = left_chopstick;
  op[0].sem_op = status;
  op[0].sem_flag = 0;

  op[1].sem_num = right_chopstick;
  op[1].sem_op = status;
  op[1].sem_flag = 0;

  sem_op(sem_id,op,2);
}

int main()
{
  //create sempahore
  for(int i=0;i<NUM_OF_PHILOSOPHER;i++)
  {
    chopsticks[i] = semget(SEMKEY,1,600);
    semctl(chopsticks[i],0,SETVAL,1);
  }
  
  //create thread for each philospher
  for(int i=0;i<NUM_OF_PHILOSOPHER;i++)
   pthread_create(&philosopher[i],NULL,runner,(void*)&i);
  
  for(int i=0;i<NUM_OF_PHILOSOPHER;i++)
   pthread_join(philosopher[i],NULL);
  
  return 0; 
}bnmbmbmmbbmbmmbmbmbbmbmbmb  
