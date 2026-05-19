#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
    // Socket descriptors
    int server_fd, client_fd;

    // Structures to store server and client address
    struct sockaddr_in server_addr, client_addr;

    // Variable to store client address size
    socklen_t len = sizeof(client_addr);

    // Buffer to store received data
    char buffer[1024];

    // Create TCP socket
    // AF_INET -> IPv4
    // SOCK_STREAM -> TCP
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // Check socket creation
    if(server_fd < 0)
    {
        printf("Socket creation failed\n");
        return 0;
    }

    // Set IPv4 address family
    server_addr.sin_family = AF_INET;

    // Set port number = 8080
    server_addr.sin_port = htons(8080);

    // Accept connection from any IP address
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket with IP and port
    bind(server_fd,
         (struct sockaddr*)&server_addr,
         sizeof(server_addr));

    // Listen for incoming clients
    // 5 = maximum waiting clients
    listen(server_fd, 5);

    printf("Waiting for client...\n");

    // Accept client connection
    // Creates new communication socket
    client_fd = accept(server_fd,
                      (struct sockaddr*)&client_addr,
                      &len);

    // Infinite loop for continuous communication
    while(1)
    {
        // Receive frame from client
        recv(client_fd,
             buffer,
             sizeof(buffer),
             0);

        // Check whether client wants to exit
        if(strcmp(buffer, "exit") == 0)
        {
            printf("Client disconnected\n");
            break;
        }

        // Print received frame
        printf("Received Frame: %s\n", buffer);

        // Send acknowledgement to client
        // This is STOP-AND-WAIT logic
        send(client_fd,
             "ACK",
             3,
             0);

        printf("ACK Sent\n");
    }

    // Close client socket
    close(client_fd);

    // Close server socket
    close(server_fd);

    return 0;
}