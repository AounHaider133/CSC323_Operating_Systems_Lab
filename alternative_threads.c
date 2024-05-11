#include<pthread.h>
#include<stdio.h>

void *runner(void*);
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int turn =0;
int main(int argc,char* argv)
{
   pthread_t t1,t2;
   pthread_attr_t attr1,attr2;

   pthread_attr_init(&attr1);
   pthread_attr_init(&attr2);

   pthread_create(&t1,&attr1,runner,NULL);
   pthread_join(t1,NULL);
   pthread_create(&t2,&attr2,runner,NULL);
   pthread_join(t2,NULL);

   return 0;
}
void *runner(void* param)
{
  int i;
  for (i = 0; i < 5; ++i)
    {
        pthread_mutex_lock(&lock);

        if (turn == 0)
        {
            printf("a\n");
            turn = 1;
        }
        else
        {
            printf("b\n");
            turn = 0;
        }

        pthread_mutex_unlock(&lock);
    }

}

