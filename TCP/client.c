#include <stdio.h>      // for printf(), scanf()
#include <string.h>     // for memset(), strlen()
#include <sys/socket.h> // for socket(), connect()
#include <netinet/in.h> // for struct sockaddr_in
#include <arpa/inet.h>  // for htons()
#include <unistd.h>     // for close()

int main()
{
    int cs, port; // initialize clientsocket, port
    struct sockaddr_in client; // initialize client socket address
    int flag, res;
    char buffer[20]; // Change response size to hold single character

    cs = socket(AF_INET, SOCK_STREAM, 0); // create socket for client with IPv4, TCP, default protocol
    client.sin_family = AF_INET; // set client socket address family to IPv4
    printf("Enter the port number: ");
    scanf("%d", &port); // get port number from user
    client.sin_port = htons(port); // Use htons() to convert port to network byte order
    connect(cs, (struct sockaddr *)&client, sizeof(client));

    do
    { // Loop until user inputs '0' (no)
        printf("\nEnter a string to check palindrome: ");
        scanf("%s", buffer);
        printf("Client: %s\n", buffer);

        send(cs, buffer, sizeof(buffer), 0); // send message to server
        
        recv(cs, &flag, sizeof(flag), 0); // receive message from server
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
    return 0;
}