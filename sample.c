#include<stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/sem.h>
#define NUM_PHILOSOPHERS 5

void *perform(void*);
pthread_t philosophers[NUM_PHILOSOPHERS];
int sem_id;

int main()
{

    //for storing temporary ids to avoid invalid results during multi-threading
    int ids[NUM_PHILOSOPHERS];

    //create semaphore to store philosphers
    sem_id = semget(IPC_PRIVATE, NUM_PHILOSOPHERS, IPC_CREAT | 0666);

    //create thread for each philosopher
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        ids[i] = i;
        semctl(sem_id, i, SETVAL, 1); //set all values of semaphore block to '1'
        pthread_create(&philosophers[i], NULL, perform, &ids[i]);
    }

    //exit all threads created
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        pthread_join(philosophers[i], NULL);
    }
    
    //delete semaphore to avoid manual delete via commands
    semctl(sem_id,0,IPC_RMID,0);
    return 0;
}

void *perform(void *args) {
    int id = *((int *)args);
    struct sembuf ops[2];
    int left = id;
    int right = (id + 1) % NUM_PHILOSOPHERS;

    //execute infinitely
    while (true) {

        printf("Philosopher #%d wants to eat\n", id);

	printf("Philosopher #%d going to eat\n", id);
        
        //consume forks
        ops[0].sem_num = left;
        ops[0].sem_op = -1;
        ops[0].sem_flg = SEM_UNDO;        
        ops[1].sem_num = right;
        ops[1].sem_op = -1;
        ops[1].sem_flg = SEM_UNDO;      

        semop(sem_id, ops, 2); //apply two operations on semaphore
        printf("philosopher #%d done eating,now going to think\n", id);

        ops[0].sem_num = left;
        ops[0].sem_op = 1;
        ops[0].sem_flg = SEM_UNDO;        
        ops[1].sem_num = right;
        ops[1].sem_op = 1;
        ops[1].sem_flg = SEM_UNDO;      

        semop(sem_id, ops, 2); //apply two operations on semaphore
        sleep(rand() % 3 + 1); //sleep for random ammount of time
    }
}
