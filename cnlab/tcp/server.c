#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
    // Server socket descriptor
    //listening socket
    int server_fd;

    // Client socket descriptor
    //used after accepting client and used to send and receive data from client
    int client_fd;

    // Structure to store server address and client address
    struct sockaddr_in server_addr, client_addr;
  

    // Variable to store size of client address
    socklen_t len = sizeof(client_addr);

    // Buffer to store messages
    char buffer[1024];

    // Create TCP socket
    // AF_INET -> IPv4
    // SOCK_STREAM -> TCP protocol
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // Check socket creation
    if(server_fd < 0)
    {
        printf("Socket creation failed\n");
        return 0;
    }

    // Set IPv4
    server_addr.sin_family = AF_INET;

    // Set port number = 8080
    server_addr.sin_port = htons(8080);

    // Accept connection from any IP address
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket with IP and port
    bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // Listen for incoming client connections
    // 5 = maximum waiting clients
    listen(server_fd, 5);

    printf("Waiting for client...\n");

    // Accept client connection
    client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &len);

    // Print client IP address
    printf("Client IP Address: %s\n", inet_ntoa(client_addr.sin_addr));

    // Print client port number
    printf("Client Port Number: %d\n", ntohs(client_addr.sin_port));

    // Receive message from client
    recv(client_fd, buffer, sizeof(buffer), 0);

    // Print client message
    printf("Client Message: %s\n", buffer);

    // Send reply to client
    send(client_fd, "Hello Client", 12, 0);

    // Close client socket
    close(client_fd);

    // Close server socket
    close(server_fd);

    return 0;
}