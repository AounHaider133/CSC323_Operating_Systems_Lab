#include<stdio.h>
#include<signal.h>
#include<unistd.h>

int testignore(int signo)
{
  struct sigaction act;
  if((sigaction(signo,NULL,&act) == -1) || (act.sa_handler != SIG_IGN))
   return 0;
  
  return 1;
}
void catchctrlc()
{
 char handmsg[] = "\nI found Ctrl-C, I am new handler :)\n";
 int msglen = sizeof(handmsg);
 write(STDOUT_FILENO,handmsg,msglen); //async sig safe
}

int main()
{
  struct sigaction act;
  act.sa_handler = catchctrlc;
  //act.sa_handler = SIG_DFL;
  act.sa_flags = 0;
  
  if((sigemptyset(&act.sa_mask)==-1) || (sigaction(SIGINT,&act,NULL) == -1))
   perror("Failed to set SIGINT to handler Ctrl-C.");
  
  sleep(5); //press Ctrl-C to see the handler
  
  return 0;
}

