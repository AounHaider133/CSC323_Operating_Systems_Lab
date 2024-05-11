#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main(int argc,char* argv[])
{
  char c;
  int file_descriptor;
  
  if((file_descriptor = open("temp.txt",O_RDONLY)) == -1)
  {
    perror("Unable to open file");
    return 1;
  }
  if(fork() == -1)
  {
    perror("Unable to fork");
    return 1;
  }

  read(file_descriptor,&c,1);
  printf("File offset: %d\n",file_descriptor);
  printf("Process %ld got %c\n",(long)getpid(),c);

  return 0;
}
