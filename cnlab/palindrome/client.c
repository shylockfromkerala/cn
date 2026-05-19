#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
    int sockfd;

    struct sockaddr_in server_addr;

    char buffer[1024];

    // Create TCP socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Server details
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to server
    connect(sockfd,
           (struct sockaddr*)&server_addr,
           sizeof(server_addr));

    // Input string
    printf("Enter string: ");
    //  scanf("%s", buffer);
    fgets(buffer, sizeof(buffer), stdin);

    // Send to server
    send(sockfd, buffer, strlen(buffer), 0);

    // Receive result
    recv(sockfd, buffer, sizeof(buffer), 0);

    // Print result
    printf("Result from server: %s\n", buffer);

    close(sockfd);

    return 0;
}