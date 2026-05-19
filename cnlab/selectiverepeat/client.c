// ================= CLIENT : SELECTIVE REPEAT =================

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>

struct Frame
{
    int data;
};

int main()
{
    int sockfd;

    struct sockaddr_in serverAddr;

    socklen_t addr_size;

    struct Frame frame;

    int ack;

    int total_frames;

    int window_size;

    struct timeval tv;

    // Create UDP socket
    sockfd = socket(AF_INET,
                    SOCK_DGRAM,
                    0);

    // Timeout = 2 seconds
    tv.tv_sec = 2;
    tv.tv_usec = 0;

    setsockopt(sockfd,
               SOL_SOCKET,
               SO_RCVTIMEO,
               &tv,
               sizeof(tv));

    // Server details
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5000);
    serverAddr.sin_addr.s_addr =
            inet_addr("127.0.0.1");

    addr_size = sizeof(serverAddr);

    printf("Enter Total Frames : ");
    scanf("%d", &total_frames);

    printf("Enter Window Size : ");
    scanf("%d", &window_size);

    // To store ACK status
    int received_ack[100] = {0};

    int base = 0;

    while(base < total_frames)
    {
        // Send all frames in current window
        for(int i = base;
            i < base + window_size &&
            i < total_frames;
            i++)
        {
            // Send only unacknowledged frames
            if(received_ack[i] == 0)
            {
                frame.data = i;

                int random = rand() % 100;

                // 80% probability frame sent
                if(random < 80)
                {
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
                    printf("\n[CLIENT] Frame %d Lost\n",
                            i);
                }
            }
        }

        // Receive ACKs for each frame
        while(1)
        {
            int n = recvfrom(sockfd,
                             &ack,
                             sizeof(ack),
                             0,
                             NULL,
                             NULL);

            if(n > 0)
            {
                printf("\n[CLIENT] ACK %d Received\n",
                        ack);

                // Mark frame acknowledged
                received_ack[ack] = 1;
            }
            else
            {
                // Timeout
                printf("\n[CLIENT] Timeout\n");
                break;
            }
        }

        // Slide window forward
        while(received_ack[base] == 1)
        {
            base++;
        }
    }

    close(sockfd);

    return 0;
}