smtp client
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {

    int sockfd;

    char buffer[1024];
    char sender[100];
    char receiver[100];
    char message[500];

    struct sockaddr_in serverAddr;

    // Create TCP socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(2525);
    serverAddr.sin_addr.s_addr =
        inet_addr("127.0.0.1");

    // Connect to server
    connect(sockfd,
            (struct sockaddr*)&serverAddr,
            sizeof(serverAddr));

    // Receive greeting
    recv(sockfd, buffer, sizeof(buffer), 0);

    printf("Server: %s\n", buffer);

    // Send HELO
    strcpy(buffer, "HELO localhost");

    send(sockfd,
         buffer,
         strlen(buffer),
         0);

    recv(sockfd, buffer, sizeof(buffer), 0);

    printf("Server: %s\n", buffer);

    // Input sender mail
    printf("Enter Sender Mail ID: ");
    scanf("%s", sender);

    sprintf(buffer,
            "MAIL FROM:<%s>",
            sender);

    send(sockfd,
         buffer,
         strlen(buffer),
         0);

    recv(sockfd, buffer, sizeof(buffer), 0);

    printf("Server: %s\n", buffer);

    // Input receiver mail
    printf("Enter Receiver Mail ID: ");
    scanf("%s", receiver);

    sprintf(buffer,
            "RCPT TO:<%s>",
            receiver);

    send(sockfd,
         buffer,
         strlen(buffer),
         0);

    recv(sockfd, buffer, sizeof(buffer), 0);

    printf("Server: %s\n", buffer);

    // Send DATA command
    strcpy(buffer, "DATA");

    send(sockfd,
         buffer,
         strlen(buffer),
         0);

    recv(sockfd, buffer, sizeof(buffer), 0);

    printf("Server: %s\n", buffer);

    // Input mail message
    getchar();

    printf("Enter Mail Message: ");
    fgets(message, sizeof(message), stdin);

    // Send mail body
    send(sockfd,
         message,
         strlen(message),
         0);

    // Send QUIT command
    strcpy(buffer, "QUIT");

    send(sockfd,
         buffer,
         strlen(buffer),
         0);

    recv(sockfd, buffer, sizeof(buffer), 0);

    printf("Server: %s\n", buffer);

    // Close socket
    close(sockfd);

    return 0;
}