#include<stdio.h>

// Structure for each router
struct router
{
    // Stores distance/cost to all routers
    unsigned cost[20];

    // Stores next hop router
    unsigned from[20];
}

// Array of routing tables for routers
routingTable[10];

int main()
{
    // Cost matrix entered by user
    int costmat[20][20];

    // Number of routers
    int routers;

    // Loop variables
    int i, j, k;

    // Input number of routers
    printf("Enter the number of routers: ");
    scanf("%d", &routers);

    // Input cost matrix
    printf("Enter the cost matrix:\n");

    for(i = 0; i < routers; i++)
    {
        for(j = 0; j < routers; j++)
        {
            // Read cost between routers
            scanf("%d", &costmat[i][j]);

            // Distance from router to itself is always 0
            costmat[i][i] = 0;

            // Initialize routing table cost
            routingTable[i].cost[j] = costmat[i][j];

            // Initially next hop is destination itself
            routingTable[i].from[j] = j;
        }
    }

    // Variable to check whether
    // another shorter path exists
    int otherShorterPathExists;

    // Repeat until no shorter path is found
    do
    {
        // Assume no shorter path initially
        otherShorterPathExists = 0;

        // Source router
        for(i = 0; i < routers; i++)
        {
            // Destination router
            for(j = 0; j < routers; j++)
            {
                // Intermediate router
                for(k = 0; k < routers; k++)
                {
                    // Check whether path through k
                    // is shorter than current path
                    if(routingTable[i].cost[j] >
                       costmat[i][k] +
                       routingTable[k].cost[j])
                    {
                        // Update shortest distance
                        routingTable[i].cost[j] =
                        costmat[i][k] +
                        routingTable[k].cost[j];

                        // Update next hop router
                        routingTable[i].from[j] = k;

                        // Shorter path found
                        otherShorterPathExists = 1;
                    }
                }
            }
        }

    }
    while(otherShorterPathExists != 0);

    // Print final routing tables
    for(i = 0; i < routers; i++)
    {
        printf("\n\nFor Router %d\n", i + 1);

        for(j = 0; j < routers; j++)
        {
            printf("Router %d via %d Distance %d\n",
                   j + 1,
                   routingTable[i].from[j] + 1,
                   routingTable[i].cost[j]);
        }
    }

    printf("\n");

    return 0;
}