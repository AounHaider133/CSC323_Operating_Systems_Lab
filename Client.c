#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<error.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<netdb.h>

int main(int argc, char *argv[])
{
  char c;
  int sockfd,portno,n,term_con = 0;
  struct sockaddr_in serv_addr;
  struct hostent *server;
  
  if(argc < 3)
  {
    fprintf(stderr,"Usage %s hostname port\n",argv[0]);
    exit(0);
  }
  
  portno = atoi(argv[2]);
  sockfd = socket(AF_INET,SOCK_STREAM,0);
  if(sockfd < 0)
  {
    fprintf(stderr,"Error while creating socket!");
    exit(0);
  }
  server = gethostbyname(argv[1]);
  serv_addr.sin_family = AF_INET;
  bcopy((char*)server->h_addr,(char*)&serv_addr.sin_addr.s_addr,server->h_length);
  serv_addr.sin_port = portno;
  
  if(connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0)
   perror("ERROR connecting.");
  
  while(1)
  {
    printf("Enter a single character");
    c = (char)getc(stdin);
    getc(stdin);
    n = write(sockfd,&c,1);
    if(n<0)
     perror("Error while writing to socket!");
    
    n = read(sockfd,&c,1);
    if(n<0)
     perror("Error reading from socket");
    
    printf("I got :%c from server\n",c);
  }

}
