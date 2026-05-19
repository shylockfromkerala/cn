#include<stdio.h>

int main()
{
    // Maximum capacity of bucket
    int bucket_size;

    // Rate at which packets leave
    int output_rate;

    // Total number of packets
    int packets;

    // Incoming packet size
    int incoming;

    // Current data stored in bucket
    int stored = 0;

    // Input bucket size
    printf("Enter Bucket Size : ");
    scanf("%d", &bucket_size);

    // Input output rate
    printf("Enter Output Rate : ");
    scanf("%d", &output_rate);

    // Input number of packets
    printf("Enter Number of Packets : ");
    scanf("%d", &packets);

    // Process packets one by one
    for(int i = 0; i < packets; i++)
    {
        // Input incoming packet size
        printf("\nEnter Incoming Packet Size : ");
        scanf("%d", &incoming);

        // Check whether packet fits in bucket
        if(stored + incoming <= bucket_size)
        {
            // Add packet to bucket
            stored += incoming;

            printf("Packet Added\n");

            // Display current bucket content
            printf("Current Bucket Content = %d\n",
                    stored);
        }
        else
        {
            // Bucket full
            printf("Bucket Overflow\n");

            // Packet discarded
            printf("Packet Dropped\n");
        }

        // Transmit data at fixed output rate
        stored -= output_rate;

        // Bucket content cannot be negative
        if(stored < 0)
        {
            stored = 0;
        }

        // Display remaining bucket content
        printf("After Transmission = %d\n",
                stored);
    }

    return 0;
}