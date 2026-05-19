// ================= SERVER : SELECTIVE REPEAT =================

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

    int ack;

    // To store received frames
    int received[100] = {0};

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

        // If frame not received earlier
        if(received[frame.data] == 0)
        {
            received[frame.data] = 1;

            ack = frame.data;

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
                printf("[SERVER] ACK %d Lost\n",
                        ack);
            }
        }
        else
        {
            // Duplicate frame
            ack = frame.data;

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