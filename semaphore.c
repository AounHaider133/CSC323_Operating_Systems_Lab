#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<time.h>
#include<sys/sem.h>
#define NUM_OF_PHILOSOPHER 5
#define SEMKEY 133

pthread_t philosopher[NUM_OF_PHILOSOPHER];
int sem_id;

void chopsticks_op(int,int);
void *runner(void*);

int main()
{
 //create semaphore array
 if((sem_id = semget(SEMKEY,5,600))==-1)
 {
   printf("Error while creating semaphore\n");
   return 1;
 }
  
  int temp[5]; 
  int i;

  //create threads
  for(i=0;i<NUM_OF_PHILOSOPHER;i++){
   temp[i] = i;
   semctl(sem_id,i,SETVAL,1);
   pthread_create(&philosopher[i],NULL,runner,(void*)&temp[i]);
  }
  
  for(i=0;i<NUM_OF_PHILOSOPHER;i++)
   pthread_join(philosopher[i],NULL);
  
  return 0; //exit
}

void *runner(void* param){
 int philosopher_id = *((int*)param);
 srand(time(NULL));
 
 while(1){
  printf("philosopher # %d wants to eat\n",philosopher_id);
 
  printf("philosopher # %d going to eat\n",philosopher_id);
  chopsticks_op(philosopher_id,-1);
 
  printf("philosopher # %d done eating, now going to think\n",philosopher_id);
  chopsticks_op(philosopher_id,1);
  sleep(rand()%4+1);
 }
}

void chopsticks_op(int philosopher_id, int status)
{
  struct sembuf op[3];
  int left_chopstick = philosopher_id;
  int right_chopstick = (philosopher_id + 1) % NUM_OF_PHILOSOPHER;

  // Now pick the left and right chopstick
  op[0].sem_num = left_chopstick;
  op[0].sem_op = status;
  op[0].sem_flg = 0;

  op[1].sem_num = right_chopstick;
  op[1].sem_op = status;
  op[1].sem_flg = 0;

  //apply the saved changes
  semop(sem_id, op, 2);
}
