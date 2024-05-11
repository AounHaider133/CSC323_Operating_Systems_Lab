#include<unistd.h>

void handler()
{
  char handmsg[] = "\nI am so sad, my child just died.\n";
  int msglen = sizeof(handmsg);
  write(STDOUT_FILENO,handmsg,msglen); //async sig safe
}
