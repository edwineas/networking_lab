#include <stdio.h>      // for printf(), scanf(), FILE, fopen(), fgets(), fclose()
#include <string.h>     // for memset()
#include <sys/socket.h> // for socket(), bind(), listen(), accept()
#include <netinet/in.h> // for struct sockaddr_in
#include <arpa/inet.h>  // for htons(), INADDR_ANY
#include <unistd.h>     // for close(), read(), write()

#define MAX 60

void main(int afg, char *argv){
     
     int ss, cs, len, port;
     struct sockaddr_in server, client;
     char fname[MAX],buff[MAX];
     FILE *f1;

     ss = socket(AF_INET, SOCK_STREAM, 0);

     server.sin_family = AF_INET;
     server.sin_addr.s_addr = INADDR_ANY;

     printf("Enter the port number: ");
     scanf("%d", &port);
     server.sin_port = htons(port);

     bind(ss, (struct sockaddr *)&server, sizeof(server));

     printf("\nListening...");
     listen(ss, 1);

     len = sizeof(client);
     cs = accept(ss, (struct sockaddr *)&client, &len);

     close(ss);

     read(cs, &fname, MAX);

     printf("\nClient message\n File Name : %s\n", fname);

     f1 = fopen(fname, "r");
     while (fgets(buff, MAX, f1) != NULL)
     {
          write(cs, buff, MAX);
     }

     fclose(f1);

     printf("\nFile Transferred\n");
}