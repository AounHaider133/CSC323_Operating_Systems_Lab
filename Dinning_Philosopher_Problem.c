#include<stdio.h>
#include<semaphore.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<time.h>
#include<sys/sem.h>
#define NUM_OF_PHILOSOPHER 5
#define SEMKEY 133

int chopsticks[NUM_OF_PHILOSOPHER];
pthread_t philosopher[NUM_OF_PHILOSOPHER];
int sem_id;

void chopsticks_op(int,int);
void *runner(void*);

int main()
{
  int temp[5];

  //access semaphore of id:133 and initilize all to 0
  for(int i=0;i<NUM_OF_PHILOSOPHER;i++)
  {
    chopsticks[i] = semget(SEMKEY,1,0666);
    semctl(chopsticks[i],0,SETVAL,1);
  }
  
  //create semaphore
  sem_id = semget(SEMKEY,1,0666);
  semctl(sem_id,0,SETVAL,4);
  
  //create thread for each philospher
  for(int i=0;i<NUM_OF_PHILOSOPHER;i++){
   temp[i] = i;
   pthread_create(&philosopher[i],NULL,runner,(void*)&temp[i]);
   }
  
  for(int i=0;i<NUM_OF_PHILOSOPHER;i++)
   pthread_join(philosopher[i],NULL);
  
  return 0; 
}

void *runner(void* param){
 int philosopher_id = *((int*)param);
 srand(time(NULL));
 
 while(1){
  printf("philosopher # %d wants to eat\n",philosopher_id);
 
  chopsticks_op(philosopher_id,-1);
  printf("philosopher # %d going to eat\n",philosopher_id);
  sleep(rand()%3+1);
 
  printf("philosopher # %d done eating, now going to think\n",philosopher_id);
  chopsticks_op(philosopher_id,1);
  sleep(rand()%3+1);
 }
}

void chopsticks_op(int philosopher_id, int status)
{
  struct sembuf op[3];
  int left_chopstick = philosopher_id;
  int right_chopstick = (philosopher_id + 1) % NUM_OF_PHILOSOPHER;

//if philosopher wants to pick chopstick
if(status == 1){
  // Try to pick right chopstick first
  op[0].sem_num = right_chopstick;
  op[0].sem_op = 0;
  op[0].sem_flg = 0;

  semop(sem_id, op, 1);

  // If the right chopstick is not available, release the left chopstick and return
  if (op[0].sem_op == -1)
  {
    op[0].sem_num = left_chopstick;
    op[0].sem_op = 1;
    op[0].sem_flg = 0;
    semop(sem_id, op, 1);
    return;
  }
 }

  // Now pick the left chopstick
  op[0].sem_num = left_chopstick;
  op[0].sem_op = status;
  op[0].sem_flg = 0;

  op[1].sem_num = right_chopstick;
  op[1].sem_op = status;
  op[1].sem_flg = 0;

  semop(sem_id, op, 2);
}
