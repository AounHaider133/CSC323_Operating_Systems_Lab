//Name: Aoun-Haider
//ID: FA21-BSE-133
//Midterm Lab Exam
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<errno.h>

int main()
{
  pid_t c1_pid,c2_pid;
  int pipe1_ds[2],pipe2_ds[2];
  
  if(pipe(pipe1_ds) == -1)
  {
    perror("Unable to create pipe");
    return 1;
  }
  
  dup2(pipe1_ds[1],STDOUT_FILENO);
  close(pipe1_ds[1]); close(pipe1_ds[0]);
  execl("/usr/bin/ls","ls",NULL);
  
  if((c1_pid=fork()) == -1)
  {
    perror("Unable to create child");
    return 1;
  }
  
  if(c1_pid == 0)
  {
    if(pipe(pipe2_ds) == -1)
    {
      perror("Unable to create 2nd pipe");
      return 1;
    }
    
    dup2(pipe1_ds[0],STDIN_FILENO);
    dup2(pipe2_ds[1],STDOUT_FILENO);
    execl("/usr/bin/grep","grep","c",NULL);
    close(pipe1_ds[1]); close(pipe1_ds[0]);
    close(pipe2_ds[1]); close(pipe2_ds[0]);
    
    if((c2_pid=fork()) == -1)
    {
      perror("Unable to create 2nd child");
      return 1;
    }
    if(c2_pid == 0)
    {
       dup2(pipe2_ds[0],STDIN_FILENO);
       execl("/usr/bin/sort","sort",NULL);
       close(pipe2_ds[1]); close(pipe2_ds[0]);   
    }
  }
  
  return 0;
}
