#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

// Structure for frame
// Here each frame contains only one integer data
struct Frame
{
    int data;
};

int main()
{
    // UDP socket descriptor
    int sockfd;

    // Structures for server and client addresses
    struct sockaddr_in serverAddr, clientAddr;

    // Variable to store address size
    socklen_t addr_size;

    // Frame variable to receive data
    struct Frame frame;

    // Variable for acknowledgement
    int ack;

    // Create UDP socket
    // AF_INET -> IPv4
    // SOCK_DGRAM -> UDP
    sockfd = socket(AF_INET,
                    SOCK_DGRAM,
                    0);

    // Set IPv4
    serverAddr.sin_family = AF_INET;

    // Set port number = 5000
    serverAddr.sin_port = htons(5000);

    // Accept packets from any IP address
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket with IP and port
    bind(sockfd,
         (struct sockaddr*)&serverAddr,
         sizeof(serverAddr));

    // Store client address size
    addr_size = sizeof(clientAddr);

    // Infinite loop for continuous communication
    while(1)
    {
        // Receive frame from client
        recvfrom(sockfd,
                 &frame,
                 sizeof(frame),
                 0,
                 (struct sockaddr*)&clientAddr,
                 &addr_size);

        // Print received frame
        printf("\n[SERVER] Frame %d Received\n",
                frame.data);

        // Generate random number between 0 and 99
        int random = rand() % 100;

        // 80% probability ACK will be sent
        if(random < 80)
        {
            // ACK number = frame number + 1
            ack = frame.data + 1;

            // Send ACK to client
            sendto(sockfd,
                   &ack,
                   sizeof(ack),
                   0,
                   (struct sockaddr*)&clientAddr,
                   addr_size);

            printf("[SERVER] ACK %d Sent\n",
                    ack);
        }
        else
        {
            // Simulate ACK loss
            printf("[SERVER] ACK Lost\n");
        }
    }

    // Close socket
    close(sockfd);

    return 0;
}