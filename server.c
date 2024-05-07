#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

void main(){
    int ss,cs,port,len;
    struct sockaddr_in server, client;
    socklen_t len;
    char b1[20];

    ss = socket(AF_INET,SOCK_STREAM,0);
    server.sin_family = AF_INET;
    printf("Enter the port number : ");
    scanf("%d",&port);
    server.sin_port=htons(port);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(ss,(struct sockaddr*)&server,sizeof(server));

    listen(ss,1);
    printf("Listening for client communication");

    len = sizeof(client);
    cs = accept(ss,(struct sockaddr*)&client,&len);
    printf("Client Connected");

    for(;;){
        memset(b1,0,sizeof(b1));
        int  byte_recev = recv(cs,b1,sizeof(b1),0);
        if (byte_recev == 0){
            printf("connection closed");
            break;
        }
        print("\n The string received")
    }
}

