/* Create a thread that will print prime numbers less n passed via command line argument*/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<pthread.h>

void *print_primes(void*);
bool isprime(int);
int main(int argc,char* argv[])
{
  if(argc < 2)
  {
    fprintf(stderr,"Usage:%s\n",argv[0]);
    return 1;
  }

  pthread_t t1;
  pthread_create(&t1,NULL,print_primes,(void*)argv[1]);
  pthread_join(t1,NULL);
  
  return 0;
}

void *print_primes(void* param)
{
  char *c = (char*)param;
  int n = atoi(c);
  printf("Prime numbers are:\n");
  for(int i=2; i<n;i++)
  {
    if(isprime(i)) printf("%d ",i);
  }
  printf("\n");
}
bool isprime(int n)
{
  if(n<=1)
   return 0;
   
  for(int i=2; i*i<=n; i++)
  {
    if(n%i == 0)
     return false;
  }
  
  return true;
}
