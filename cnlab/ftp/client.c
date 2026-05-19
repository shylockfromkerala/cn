ftp client 
/* FTP CLIENT PROGRAM */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {

    int sockfd;

    char buffer[1024];

    struct sockaddr_in serverAddr;

    // Create TCP socket
    sockfd = socket(AF_INET,
                    SOCK_STREAM,
                    0);

    // Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(6265);

    serverAddr.sin_addr.s_addr =
        inet_addr("127.0.0.1");

    // Connect to server
    connect(sockfd,
            (struct sockaddr*)&serverAddr,
            sizeof(serverAddr));

    // Input filename
    printf("Enter File Name: ");
    scanf("%s", buffer);

    // Send filename to server
    send(sockfd,
         buffer,
         strlen(buffer),
         0);

    printf("\nFile Content:\n\n");

    // Receive file data continuously
    while (recv(sockfd,
                buffer,
                sizeof(buffer),
                0) > 0) {

        // Display received data
        printf("%s", buffer);

        // Clear buffer
        memset(buffer, 0, sizeof(buffer));
    }

    // Close socket
    close(sockfd);

    return 0;
}