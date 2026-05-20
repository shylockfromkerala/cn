#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
    int sockfd, newSocket;

    struct sockaddr_in serverAddr, clientAddr;

    socklen_t addr_size;

    int num, temp, rem;

    int digits = 0;

    int sum = 0;

    char result[100];

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

    // Receive number
    recv(newSocket,
         &num,
         sizeof(num),
         0);

    printf("Number Received : %d\n", num);

    temp = num;

    // Count digits
    while(temp > 0)
    {
        digits++;

        temp = temp / 10;
    }

    temp = num;

    // Find Armstrong sum
    while(temp > 0)
    {
        rem = temp % 10;

        sum = sum + pow(rem, digits);

        temp = temp / 10;
    }

    // Check Armstrong
    if(sum == num)
    {
        strcpy(result, "Armstrong Number");
    }
    else
    {
        strcpy(result, "Not Armstrong Number");
    }

    // Send result
    send(newSocket,
         result,
         sizeof(result),
         0);

    close(newSocket);

    close(sockfd);

    return 0;
}