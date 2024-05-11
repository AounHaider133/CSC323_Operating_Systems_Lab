#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>

void handler();

int main()
{
     pid_t pid;
     struct sigaction act;
	
     act.sa_handler = handler;
     printf("Signal handler attached for SIGCHLD\n");
     act.sa_flags = 0;
	 
     if((sigemptyset(&act.sa_mask) == -1) || (sigaction(SIGCHLD,&act,NULL))){
        perror("Failed to set SIGCHLD handler\n");
        return 1;
     }

     if((pid = fork()) == -1)
     {
       perror("Failed to fork\n");
       return 1;
     }
   
   if(pid == 0)
   {
      printf("I am child with PID = %ld and  I am going to run ls\n",(long)getpid());
      execl("/bin/ls","ls",NULL);
//      kill(getppid(), SIGCHLD);  
      return 1;
   }
   
   if(wait(NULL) == -1)
   {
     perror("Parent failed to wait for child\n");
     return 1;
   }   
 
   return 0;   
}
