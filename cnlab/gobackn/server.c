#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>

struct Frame
{
    int data;
};

int main()
{
    int sockfd;

    struct sockaddr_in serverAddr,
                       clientAddr;

    socklen_t addr_size;

    struct Frame frame;

    int expected = 0;

    int ack;

    // Create UDP socket
    sockfd = socket(AF_INET,
                    SOCK_DGRAM,
                    0);

    // Server details
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5000);
    serverAddr.sin_addr.s_addr =
            INADDR_ANY;

    // Bind socket
    bind(sockfd,
         (struct sockaddr*)&serverAddr,
         sizeof(serverAddr));

    addr_size = sizeof(clientAddr);

    while(1)
    {
        recvfrom(sockfd,
                 &frame,
                 sizeof(frame),
                 0,
                 (struct sockaddr*)&clientAddr,
                 &addr_size);

        printf("\n[SERVER] Frame %d Received\n",
                frame.data);

        // Correct frame received
        if(frame.data == expected)
        {
            expected++;

            ack = expected;

            int random = rand() % 100;

            // 80% probability ACK sent
            if(random < 80)
            {
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
                printf("[SERVER] ACK Lost\n");
            }
        }
        else
        {
            // Wrong frame received
            // Send last ACK again
            ack = expected;

            sendto(sockfd,
                   &ack,
                   sizeof(ack),
                   0,
                   (struct sockaddr*)&clientAddr,
                   addr_size);

            printf("[SERVER] Duplicate ACK %d Sent\n",
                    ack);
        }
    }

    close(sockfd);

    return 0;
}