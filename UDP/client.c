#include <stdio.h>      // for printf(), scanf()
#include <string.h>     // for memset(), strlen()
#include <sys/socket.h> // for socket(), sendto(), recvfrom()
#include <netinet/in.h> // for struct sockaddr_in
#include <arpa/inet.h>  // for htons()
#include <unistd.h>     // for close()

void main(){

    int cs, port; // initialize clientsocket, port
    struct sockaddr_in server; // initialize client socket address
    socklen_t len; // initialize length of socket
    
    int flag, res;
    char buffer[20]; // Change response size to hold single character

    cs = socket(AF_INET, SOCK_DGRAM, 0); // create socket for client with IPv4, UDP, default protocol
    len = sizeof(server); // set length of client socket address
    server.sin_family = AF_INET; // set server socket address family to IPv4
    printf("Enter the port number: ");
    scanf("%d", &port); // get port number from user
    server.sin_port = htons(port); // Use htons() to convert port to network byte order

    do
    { // Loop until user inputs '0' (no)
        printf("\nEnter a string to check palindrome: ");
        scanf("%s", buffer);
        printf("Client: %s\n", buffer);

        sendto(cs, buffer, sizeof(buffer), 0, (struct sockaddr *)&server, sizeof(server)); // send message to server
        
        recvfrom(cs, &flag, sizeof(flag), 0, (struct sockaddr *)&server, &len); // receive message from server

        if (flag == 1){
            printf("Server: the string is a palindrome.\n");
        }
        else{
            printf("Server: the string is not a palindrome.\n");
        }
        printf("\nDo you want to continue? (1 for yes, 0 for no): ");
        scanf("%d", &res);
    } while (res == 1); // Loop until user inputs '0' (no)

    close(cs);
}