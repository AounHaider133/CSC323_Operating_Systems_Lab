#include<stdio.h>

int main()
{
  int num;
  for(int i=0; i<10; i++)
  {
    printf("%d: ",i);
    scanf("%d",&num);
    fprintf(stderr,"%d\n",num);
  }
  
  return 0;
}
