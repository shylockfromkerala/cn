#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

// Structure for frame
struct Frame
{
    int data;
};

int main()
{
    // UDP socket descriptor
    int sockfd;

    // Structure for server address
    struct sockaddr_in serverAddr;

    // Variable to store address size
    socklen_t addr_size;

    // Frame variable
    struct Frame frame;

    // Variable for ACK
    int ack;

    // Variable to store total number of frames
    int total_frames;

    // Structure for timeout
    struct timeval tv;

    // Create UDP socket
    sockfd = socket(AF_INET,
                    SOCK_DGRAM,
                    0);

    // Timeout = 2 seconds
    tv.tv_sec = 2;

    tv.tv_usec = 0;

    // Set timeout for recvfrom()
    // SO_RCVTIMEO -> Receive timeout
    setsockopt(sockfd,
               SOL_SOCKET,
               SO_RCVTIMEO,
               &tv,
               sizeof(tv));

    // Set IPv4
    serverAddr.sin_family = AF_INET;

    // Set server port number = 5000
    serverAddr.sin_port = htons(5000);

    // Set server IP address
    // 127.0.0.1 -> localhost
    serverAddr.sin_addr.s_addr =
            inet_addr("127.0.0.1");

    // Store address size
    addr_size = sizeof(serverAddr);

    // Input total frames from user
    printf("Enter Total Frames : ");

    scanf("%d", &total_frames);

    // Loop to send frames one by one
    for(int i = 0; i < total_frames; i++)
    {
        // Frame number
        frame.data = i;

        // Stop-and-Wait loop
        // Keep sending until ACK received
        while(1)
        {
            // Generate random number
            int random = rand() % 100;

            // 80% probability frame will be sent
            if(random < 80)
            {
                // Send frame to server
                sendto(sockfd,
                       &frame,
                       sizeof(frame),
                       0,
                       (struct sockaddr*)&serverAddr,
                       addr_size);

                printf("\n[CLIENT] Frame %d Sent\n",
                        i);
            }
            else
            {
                // Simulate frame loss
                printf("\n[CLIENT] Frame %d Lost\n",
                        i);
            }

            // Wait for ACK from server
            int n = recvfrom(sockfd,
                             &ack,
                             sizeof(ack),
                             0,
                             NULL,
                             NULL);

            // If ACK received successfully
            if(n > 0)
            {
                printf("[CLIENT] ACK %d Received\n",
                        ack);

                // Stop retransmission
                // Send next frame
                break;
            }
            else
            {
                // Timeout occurred
                // Retransmit same frame
                printf("[CLIENT] Timeout -> Retransmitting Frame %d\n",
                        i);
            }
        }
    }

    // Close socket
    close(sockfd);

    return 0;
}