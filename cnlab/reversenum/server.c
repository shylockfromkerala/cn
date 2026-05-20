#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
    int sockfd, newSocket;

    struct sockaddr_in serverAddr, clientAddr;

    socklen_t addr_size;

    int num;

    int reverse = 0;

    int rem;

    // Create socket
    sockfd = socket(AF_INET,
                    SOCK_STREAM,
                    0);

    // Server details
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5000);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind
    bind(sockfd,
         (struct sockaddr*)&serverAddr,
         sizeof(serverAddr));

    // Listen
    listen(sockfd, 5);

    printf("Server Waiting...\n");

    addr_size = sizeof(clientAddr);

    // Accept connection
    newSocket = accept(sockfd,
                       (struct sockaddr*)&clientAddr,
                       &addr_size);

    // Receive number
    recv(newSocket,
         &num,
         sizeof(num),
         0);

    printf("Number Received : %d\n", num);

    // Reverse number
    while(num > 0)
    {
        rem = num % 10;

        reverse = (reverse * 10) + rem;

        num = num / 10;
    }

    // Send reversed number
    send(newSocket,
         &reverse,
         sizeof(reverse),
         0);

    close(newSocket);

    close(sockfd);

    return 0;
}