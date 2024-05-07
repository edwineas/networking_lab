#include <stdio.h>      // for printf(), scanf()
#include <string.h>     // for memset(), strlen()
#include <sys/socket.h> // for socket(), bind()
#include <netinet/in.h> // for struct sockaddr_in
#include <arpa/inet.h>  // for htons(), INADDR_ANY
#include <unistd.h>     // for close()

void main()
{
    int ss, port;                      // initialize seversocket, port
    struct sockaddr_in server, client; // initialize server socket address
    socklen_t len;                     // initialize length of socket

    int i, flag, length;
    char b1[20];

    ss = socket(AF_INET, SOCK_DGRAM, 0); // create socket for server with IPv4, UDP, default protocol
    server.sin_family = AF_INET;         // set server socket address family to IPv4
    printf("Enter the port number: ");
    scanf("%d", &port);                  // get port number from user
    server.sin_port = htons(port);       // Convert port to network byte order
    server.sin_addr.s_addr = INADDR_ANY; // set server socket address to any local IP address

    bind(ss, (struct sockaddr *)&server, sizeof(server)); // bind server socket to server address

    printf("Listening for client connection...\n");

    len = sizeof(server); // set length of client socket address

    for (;;)
    {
        memset(b1, 0, sizeof(b1));                                                         // clear buffer
        int byte_recv = recvfrom(ss, b1, sizeof(b1), 0, (struct sockaddr *)&client, &len); // receive message from client

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
        // if (num == 0 || num == 1){
        //     flag = 0;
        // }
        // else{
        //     for (i = 2; i <= num / 2; i++){
        //         if (num % i == 0){
        //             flag = 0;
        //             break;
        //         }
        //     }
        // }

        // Check if the number is amstrong
        // int num = atoi(b1); // Convert string to integer
        // int sum = 0, temp, remainder, n = strlen(b1);
        // temp = num;
        // while (temp != 0){
        //     remainder = temp % 10;
        //     sum += remainder * remainder * remainder;
        //     temp /= 10;
        // }
        // if (num != sum){
        //     flag = 0;
        // }

        sendto(ss, &flag, sizeof(flag), 0, (struct sockaddr *)&client, len); // send message to client
    }
    close(ss);
}