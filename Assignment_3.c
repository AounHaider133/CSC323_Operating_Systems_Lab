#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/sem.h>

#define NUM_PHILOSOPHERS 5

int sem_id;

void *philosopher(void *arg) {
    int id = *((int *)arg);
    int num_chopsticks = NUM_PHILOSOPHERS;
    int left = (id + num_chopsticks - 1) % num_chopsticks;
    int right = (id + 1) % num_chopsticks;

    while (1) {
        printf("philosopher # %d wants to eat\n", id);

        struct sembuf pickup[2] = {
            {left, -1, SEM_UNDO},
            {right, -1, SEM_UNDO}
        };

        printf("philosopher # %d going to eat\n", id);
        semop(sem_id, pickup, 2);

        printf("philosopher # %d done eating, now going to think\n", id);

        struct sembuf putdown[2] = {
            {left, 1, SEM_UNDO},
            {right, 1, SEM_UNDO}
        };

        semop(sem_id, putdown, 2);
        sleep(rand() % 3 + 1); // Think for a random time
    }

    return NULL;
}
int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    sem_id = semget(IPC_PRIVATE, NUM_PHILOSOPHERS, IPC_CREAT | 0666);

    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosopher_ids[i] = i;
        semctl(sem_id, i, SETVAL, 1);
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        pthread_join(philosophers[i], NULL);
    }

     semctl(sem_id, 0, IPC_RMID, 0); // Clean up the semaphore
      return 0;
}
