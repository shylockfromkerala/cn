smtp server
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {

    int serverSock, clientSock;
    char buffer[1024];

    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrSize;

    // Create TCP socket
    serverSock = socket(AF_INET, SOCK_STREAM, 0);

    // Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(2525);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket
    bind(serverSock,
         (struct sockaddr*)&serverAddr,
         sizeof(serverAddr));

    // Listen for connection
    listen(serverSock, 5);

    printf("SMTP Server Waiting...\n");

    addrSize = sizeof(clientAddr);

    // Accept client connection
    clientSock = accept(serverSock,
                        (struct sockaddr*)&clientAddr,
                        &addrSize);

    // Send greeting
    strcpy(buffer, "220 SMTP Service Ready");

    send(clientSock,
         buffer,
         strlen(buffer),
         0);

    // Receive HELO
    recv(clientSock, buffer, sizeof(buffer), 0);
    printf("Client: %s\n", buffer);

    send(clientSock, "250 OK", 6, 0);

    // Receive MAIL FROM
    recv(clientSock, buffer, sizeof(buffer), 0);
    printf("Client: %s\n", buffer);

    send(clientSock, "250 OK", 6, 0);

    // Receive RCPT TO
    recv(clientSock, buffer, sizeof(buffer), 0);
    printf("Client: %s\n", buffer);

    send(clientSock, "250 OK", 6, 0);

    // Receive DATA command
    recv(clientSock, buffer, sizeof(buffer), 0);
    printf("Client: %s\n", buffer);

    send(clientSock,
         "354 Start Mail Input",
         22,
         0);

    // Receive mail body
    recv(clientSock, buffer, sizeof(buffer), 0);
    printf("\nMail Received:\n%s\n", buffer);

    // Receive QUIT
    recv(clientSock, buffer, sizeof(buffer), 0);
    printf("Client: %s\n", buffer);

    send(clientSock,
         "221 Service Closed",
         18,
         0);

    // Close sockets
    close(clientSock);
    close(serverSock);

    return 0;
}