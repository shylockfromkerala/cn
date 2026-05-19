#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
    // Socket descriptor
    int sockfd;

    // Buffer to store message
    char buffer[1024];

    // Structure to store server address
    // sockaddr_in is a structure to store IPV4 and _in means IPV4
    // server_addr is a variable of type sockaddr_in to store server address
    struct sockaddr_in server_addr;

    // Create UDP socket
    // AF_INET -> IPv4
    // SOCK_DGRAM -> UDP protocol
    // 0 means default protocol for UDP
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // Set IPv4 address family
    server_addr.sin_family = AF_INET;

    // Set server port number = 8080
    server_addr.sin_port = htons(8080);

    // Convert IP address string into network format
    // 127.0.0.1 means localhost
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Copy message into buffer
    strcpy(buffer, "Hello Server");

    // Send message to server
    //sendto(socket, data, size, flags, destination, address_size);
    sendto(sockfd, buffer, strlen(buffer), 0,
          (struct sockaddr*)&server_addr, sizeof(server_addr));

    // Receive reply from server
    //recvfrom(socket, buffer, size, flags, sender_addr, sender_addr_len);
    recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, NULL);

    // Print reply received from server
    printf("Server: %s\n", buffer);

    // Close socket
    close(sockfd);
}