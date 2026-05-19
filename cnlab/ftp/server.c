ftp server
/* FTP SERVER PROGRAM */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {

    int serverSock, clientSock;

    char buffer[1024];

    struct sockaddr_in serverAddr, clientAddr;

    socklen_t addrSize;

    FILE *fp;

    // Create TCP socket
    serverSock = socket(AF_INET,
                        SOCK_STREAM,
                        0);

    // Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(6265);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket
    bind(serverSock,
         (struct sockaddr*)&serverAddr,
         sizeof(serverAddr));

    // Listen for client
    listen(serverSock, 5);

    printf("FTP Server Waiting...\n");

    addrSize = sizeof(clientAddr);

    // Accept client connection
    clientSock = accept(serverSock,
                        (struct sockaddr*)&clientAddr,
                        &addrSize);

    // Receive filename from client
    recv(clientSock,
         buffer,
         sizeof(buffer),
         0);

    printf("Requested File: %s\n", buffer);

    // Open file in read mode
    fp = fopen(buffer, "r");

    // Check whether file exists
    if (fp == NULL) {

        strcpy(buffer, "File Not Found");

        send(clientSock,
             buffer,
             strlen(buffer),
             0);
    }
    else {

        // Read file line by line
        while (fgets(buffer,
                     sizeof(buffer),
                     fp) != NULL) {

            // Send each line to client
            send(clientSock,
                 buffer,
                 strlen(buffer),
                 0);

            // Small delay
            sleep(1);
        }

        fclose(fp);
    }

    // Close sockets
    close(clientSock);
    close(serverSock);

    return 0;
}