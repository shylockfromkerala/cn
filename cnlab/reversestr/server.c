#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
    int sockfd, newSocket;

    struct sockaddr_in serverAddr, clientAddr;

    socklen_t addr_size;

    char str[100];

    char rev[100];

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

    // Receive string
    recv(newSocket,
         str,
         sizeof(str),
         0);

    printf("String Received : %s\n", str);

    // Reverse string
    int len = strlen(str);

    int j = 0;

    for(int i = len - 1; i >= 0; i--)
    {
        rev[j] = str[i];
        j++;
    }

    rev[j] = '\0';

    // Send reversed string
    send(newSocket,
         rev,
         sizeof(rev),
         0);

    close(newSocket);

    close(sockfd);

    return 0;
}