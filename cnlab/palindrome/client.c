#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
    int sockfd;

    struct sockaddr_in serverAddr;

    char str[100];

    char result[100];

    // Create socket
    sockfd = socket(AF_INET,
                    SOCK_STREAM,
                    0);

    // Server details
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5000);
    serverAddr.sin_addr.s_addr =
            inet_addr("127.0.0.1");

    // Connect
    connect(sockfd,
            (struct sockaddr*)&serverAddr,
            sizeof(serverAddr));

    // Input
    printf("Enter String : ");
    scanf("%s", str);

    // Send string
    send(sockfd,
         str,
         sizeof(str),
         0);

    // Receive result
    recv(sockfd,
         result,
         sizeof(result),
         0);

    printf("Server Says : %s\n", result);

    close(sockfd);

    return 0;
}
