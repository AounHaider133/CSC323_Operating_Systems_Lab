#include<unistd.h>

void handler()
{
  char msg[] = "I am so said, my child just died\n";
  int len = sizeof(msg);
  write(STDOUT_FILENO,msg,len);

}
