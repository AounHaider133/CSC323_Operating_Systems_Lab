#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#define BUF_SIZE 1024
#define CREATE_FLAGS (O_WRONLY | O_CREAT | O_TRUNC)
#define CREATE_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int main(int argc,char* argv[])
{
  pid_t pid;
  int fd;
  int i,n;
  char buf[BUF_SIZE];
  
  if(argc != 3)
  {
    fprintf(stderr,"Usage: %s processes filename\n",argv[0]);
    return 1;
  }
  
  if((fd = open(argv[2],CREATE_FLAGS,CREATE_PERMS)) == -1)
  {
    fprintf(stderr,"Unable to open file: %s",argv[2]);
    return 1;
  }
  
  n = atoi(argv[1]);
  
  for(int i=1 ; i<n ; i++)
  {
    if(pid = fork())
     break;
    
    if(pid == -1)
    {
      perror("Failed to fork.");
      return 1;
    }

  }
                                                       /*Write twice to the common log*/
  sprintf(buf,"i:%d processes:%ld ",i,(long)getpid());
  write(fd,buf,strlen(buf)); 	
  sleep(1);
  sprintf(buf,"Parent: %ld Child: %ld\n",(long)getppid(),(long)pid);
  write(fd,buf,strlen(buf));
  
  return 0;   
}
