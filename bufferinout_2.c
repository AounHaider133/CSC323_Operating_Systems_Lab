#include<stdio.h>

int main(int argc,char* argv[])
{
  int a;
  fprintf(stdout,"a");
  scanf("%d",&a); //scanf flushes the buffer before taking from stdin
  fprintf(stderr,"a has been written to buffer successfully!\n");
  fprintf(stdout,"b");
  fprintf(stderr,"b has been written to buffer successfully!\n"); 
  fprintf(stdout,"\n");
  
  return 0;
}
