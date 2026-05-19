#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
    // Client socket descriptor
    int sockfd;

    // Structure to store server address
    struct sockaddr_in server_addr;

    // Buffer to store message
    char buffer[1024];

    // Create TCP socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Check socket creation
    if(sockfd < 0)
    {
        printf("Socket creation failed\n");
        return 0;
    }

    // Set IPv4
    server_addr.sin_family = AF_INET;

    // Set port number = 8080
    server_addr.sin_port = htons(8080);

    // Convert IP address into binary format
    // 127.0.0.1 = localhost
    //inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);or you can use this
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to server
    connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // Copy message into buffer
    strcpy(buffer, "Hello Server");

    // Send message to server
    send(sockfd, buffer, strlen(buffer), 0);

    // Receive reply from server
    recv(sockfd, buffer, sizeof(buffer), 0);

    // Print server reply
    printf("Server Message: %s\n", buffer);

    // Close socket
    close(sockfd);

    return 0;
}