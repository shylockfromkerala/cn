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

    // Structures to store server and client address
    struct sockaddr_in server_addr, client_addr;

    // Variable to store size of client address
    //socklen_t is a datatype to store size of socket address structure
    socklen_t len;

    // Create UDP socket
    // AF_INET -> IPv4
    // SOCK_DGRAM -> UDP protocol
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // Set address family as IPv4
    server_addr.sin_family = AF_INET;

    // Set port number = 8080
    // htons converts host byte order to network byte order
    server_addr.sin_port = htons(8080);

    // Accept connection from any IP address
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket with server address and port
    // This makes server listen on port 8080
    bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // Initialize len with size of client address
    len = sizeof(client_addr);

    // Receive message from client
    // Data received is stored in buffer
    // Client address gets stored in client_addr
    recvfrom(sockfd, buffer, sizeof(buffer), 0,
            (struct sockaddr*)&client_addr, &len);

    // Print message received from client
    printf("Client: %s\n", buffer);

    // Send reply back to client
    sendto(sockfd, "Hello Client", 12, 0,
          (struct sockaddr*)&client_addr, len);

    // Close socket
    close(sockfd);
}