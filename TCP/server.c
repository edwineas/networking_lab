#include <stdio.h>      // for printf(), scanf()
#include <string.h>     // for memset(), strlen()
#include <sys/socket.h> // for socket(), bind(), listen(), accept()
#include <netinet/in.h> // for struct sockaddr_in
#include <arpa/inet.h>  // for htons()
#include <unistd.h>     // for close()

void main()
{
    int ss, cs, port;                  // initialize seversocket, clientsocket, port
    struct sockaddr_in server, client; // initialize server and client socket address
    socklen_t len;                     // initialize length of socket
    int i, flag, length;
    char b1[20];

    ss = socket(AF_INET, SOCK_STREAM, 0); // create socket for server with IPv4, TCP, default protocol
    server.sin_family = AF_INET;          // set server socket address family to IPv4

    printf("Enter the port number: ");
    scanf("%d", &port);                  // get port number from user

    server.sin_port = htons(port);       // Convert port to network byte order
    server.sin_addr.s_addr = INADDR_ANY; // set server socket address to any local IP address

    bind(ss, (struct sockaddr *)&server, sizeof(server)); // bind server socket to server address

    listen(ss, 1); // listen for incoming connections on server socket
    printf("Listening for client connection...\n");

    len = sizeof(client);                              // set length of client socket address
    cs = accept(ss, (struct sockaddr *)&client, &len); // accept incoming connection on server socket
    printf("Connected to client...\n");

    for (;;){
        memset(b1, 0, sizeof(b1)); // clear buffer
        int byte_recv = recv(cs, b1, sizeof(b1), 0); // receive message from client

        if (byte_recv == 0)
        {
            printf("\nConnection closed\n");
            break;
        }

        printf("\nThe string received is: %s\n", b1);

        flag = 1; // set flag to 1

        // Check if string is a palindrome
        length = strlen(b1); // get length of string
        for (i = 0; i < length / 2; i++)
        {
            if (b1[i] != b1[length - i - 1])
            { // If characters do not match
                flag = 0;
                break;
            }
        }

        // Check if the number is prime
        // int num = atoi(b1); // Convert string to integer
        // for (i = 2; i <= num / 2; i++){
        //     if (num % i == 0){ // If number is divisible by i
        //         flag = 0;
        //         break;
        //     }
        // }

        // Check if the number is amstrong
        // int num = atoi(b1); // Convert string to integer
        // int sum = 0, temp = num;
        // while (temp != 0){
        //     int rem = temp % 10;
        //     sum += rem * rem * rem;
        //     temp /= 10;
        // }
        // if (num != sum){
        //     flag = 0;
        // }

        send(cs, &flag, sizeof(flag), 0); // send flag to client
    }

    close(ss); // close server socket
    close(cs); // close client socket
}