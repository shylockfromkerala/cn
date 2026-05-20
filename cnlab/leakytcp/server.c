#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>

int main()
{
    int sockfd, newSocket;

    struct sockaddr_in serverAddr, clientAddr;

    socklen_t addr_size;

    int bucket_size;

    int output_rate;

    int incoming;

    int stored = 0;

    // Create socket
    sockfd = socket(AF_INET,
                    SOCK_STREAM,
                    0);

    // Server details
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5000);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind
    bind(sockfd,
         (struct sockaddr*)&serverAddr,
         sizeof(serverAddr));

    // Listen
    listen(sockfd, 5);

    printf("Server Waiting...\n");

    addr_size = sizeof(clientAddr);

    // Accept connection
    newSocket = accept(sockfd,
                       (struct sockaddr*)&clientAddr,
                       &addr_size);

    // Receive bucket size
    recv(newSocket,
         &bucket_size,
         sizeof(bucket_size),
         0);

    // Receive output rate
    recv(newSocket,
         &output_rate,
         sizeof(output_rate),
         0);

    printf("Bucket Size : %d\n", bucket_size);
    printf("Output Rate : %d\n", output_rate);

    while(1)
    {
        // Receive incoming packet size
        recv(newSocket,
             &incoming,
             sizeof(incoming),
             0);

        // Stop condition
        if(incoming == -1)
        {
            break;
        }

        printf("\nIncoming Packet : %d\n", incoming);

        // Check overflow
        if(stored + incoming > bucket_size)
        {
            printf("Packet Dropped\n");
        }
        else
        {
            stored = stored + incoming;

            printf("Stored Data : %d\n", stored);
        }

        // Leak packets
        if(stored < output_rate)
        {
            printf("Sent : %d\n", stored);

            stored = 0;
        }
        else
        {
            printf("Sent : %d\n", output_rate);

            stored = stored - output_rate;
        }

        printf("Remaining : %d\n", stored);
    }

    close(newSocket);

    close(sockfd);

    return 0;
}