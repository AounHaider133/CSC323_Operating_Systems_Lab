#include <errno.h>
#include <pthread.h>
#include <stdio.h>

pthread_cond_t bcond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t bmutex = PTHREAD_MUTEX_INITIALIZER;
int count = 0;
int limit = 3;

int waitbarrier();

/* ARGSUSED */
static void *printthread(void *arg)
{
   fprintf(stderr, "This is the first print of the thread %d\n", (int)pthread_self());
   waitbarrier();
   fprintf(stderr, "This is the second print of the thread %d\n", (int)pthread_self());
   return NULL;
}

int main(void)
{
   pthread_t t0,t1,t2;

   if (pthread_create(&t0,NULL,printthread,NULL))
      fprintf(stderr,"Error creating thread 0.\n");
   if (pthread_create(&t1,NULL,printthread,NULL))
      fprintf(stderr,"Error creating thread 1.\n");
   if (pthread_create(&t2,NULL,printthread,NULL))
      fprintf(stderr,"Error creating thread 2.\n");
   if (pthread_join(t0,NULL))
      fprintf(stderr,"Error joining thread 0.\n");
   if (pthread_join(t1,NULL))
      fprintf(stderr,"Error joining thread 1.\n");
   if (pthread_join(t2,NULL))
      fprintf(stderr,"Error joining thread 2.\n");
   fprintf(stderr,"All threads complete.\n");
   return 0;
}

int waitbarrier(void) // wait at the barrier until all n threads arrive
{
   int berror = 0;
   int error;

   if ( error = pthread_mutex_lock(&bmutex))  //couldn't lock, give up
      return error;
   count++;
   while ((count < limit) && !berror)
      berror = pthread_cond_wait(&bcond, &bmutex);
   if(!berror)
      berror = pthread_cond_broadcast(&bcond);  // wake up everyone
   error = pthread_mutex_unlock(&bmutex);

  if(berror)
      return berror;
  return error;
}
