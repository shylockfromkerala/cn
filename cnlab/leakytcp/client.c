#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>

int main()
{
    int sockfd;

    struct sockaddr_in serverAddr;

    int bucket_size;

    int output_rate;

    int incoming;

    // Create socket
    sockfd = socket(AF_INET,
                    SOCK_STREAM,
                    0);

    // Server details
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5000);
    serverAddr.sin_addr.s_addr =
            inet_addr("127.0.0.1");

    // Connect
    connect(sockfd,
            (struct sockaddr*)&serverAddr,
            sizeof(serverAddr));

    // Input bucket details
    printf("Enter Bucket Size : ");
    scanf("%d", &bucket_size);

    printf("Enter Output Rate : ");
    scanf("%d", &output_rate);

    // Send details
    send(sockfd,
         &bucket_size,
         sizeof(bucket_size),
         0);

    send(sockfd,
         &output_rate,
         sizeof(output_rate),
         0);

    while(1)
    {
        printf("\nEnter Incoming Packet Size (-1 to stop) : ");
        scanf("%d", &incoming);

        // Send packet size
        send(sockfd,
             &incoming,
             sizeof(incoming),
             0);

        if(incoming == -1)
        {
            break;
        }
    }

    close(sockfd);

    return 0;
}