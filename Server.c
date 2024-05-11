#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/in.h>

int main(int argc,char* argv[])
{
   int sockfd;
   char c;
   int port_no,n;
   struct sockaddr_in sockaddr,cliaddr;
   socklen_t chilen;
   
   sockfd = socket(AF_INET,SOCK_STREAM,0);
   
   if(sockfd<0){
    perror("ERROR while creating socket!");
    return 1;
   }
   
   port_no = atoi(argv[1]);
   
   sockaddr.sin_family = AF_INET;
   sockaddr.sin_port = port_no;
   sockaddr.sin_addr.s_addr = INADDR_ANY;
   c = 'a';
   bind(sockfd,(struct sockaddr*)&sockaddr,sizeof(sockaddr));
   
   listen(sockfd,5);
   chilen = sizeof(cliaddr);
   while(1)
   {
   while(1){
     accept(sockfd,(struct sockaddr*)&cliaddr,&chilen);
     n = read(sockfd,&c,1);
     
     printf("I got : %c\n",c);
     ++c;
     write(sockfd,&c,1);
     }
   }   
}
