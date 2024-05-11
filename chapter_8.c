#include<stdio.h>
#include<stdlib.h>

int main(int argc,char* argv[])
{
  if(argc < 2)
    {
        printf("Usage: %s\n",argv[0]);
        return 1;
    }
    
    unsigned int logical_addr = atoi(argv[1]);
    int page_no = logical_addr >> 12;
    int offset = (logical_addr << 20)>>20;
    printf("The address %d contains:\npage no:%d\noffset: %d\n",logical_addr,page_no,offset);

    return 0;
}
