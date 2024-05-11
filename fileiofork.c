#include<stdio.h>
#include<unistd.h>

int main(int argc,char* argv[])
{
  //setvbuf(stdout,NULL,_IONBF,0);
  printf("Welcome to the CSC321- Operating Systems.");
  
  fork();
  
  return 0;
}
