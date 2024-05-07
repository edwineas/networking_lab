#include <stdio.h>      // for printf(), scanf()
#include <string.h>     // for memset()
#include <sys/socket.h> // for socket(), connect()
#include <netinet/in.h> // for struct sockaddr_in
#include <arpa/inet.h>  // for htons(), INADDR_ANY
#include <unistd.h>     // for close(), read(), write()

#define MAX 60
void main(int arg, char *argv[])
{
   int cs, n, port;
   struct sockaddr_in server;

   char fname[MAX], buff[MAX];

   cs = socket(AF_INET, SOCK_STREAM, 0);

   server.sin_family = AF_INET;
   server.sin_addr.s_addr = INADDR_ANY;
   printf("Enter the port number : ");
   scanf("%d", &port);
   server.sin_port = htons(port);

   connect(cs, (struct sockaddr *)&server, sizeof(server));

   printf("\nEnter the source file name : \n");
   scanf("%s", fname);
   write(cs, fname, MAX);

   while ((n = read(cs, buff, MAX)) != 0){
      printf("%s", buff);
   }
   printf("\n");

   close(cs);
}