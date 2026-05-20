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

    char result[100];

    int flag = 1;

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

    int len = strlen(str);

    // Check palindrome
    for(int i = 0; i < len / 2; i++)
    {
        if(str[i] != str[len - i - 1])
        {
            flag = 0;
            break;
        }
    }

    if(flag == 1)
    {
        strcpy(result, "Palindrome");
    }
    else
    {
        strcpy(result, "Not Palindrome");
    }

    // Send result
    send(newSocket,
         result,
         sizeof(result),
         0);

    close(newSocket);

    close(sockfd);

    return 0;
}
