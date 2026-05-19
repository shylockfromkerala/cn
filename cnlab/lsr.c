#include<stdio.h>

int main()
{
    // Cost matrix
    int cost[10][10];

    // Stores shortest distances
    int distance[10];

    // Checks visited nodes
    int visited[10];

    // Variables
    int i, j, n, source;

    // Minimum distance and next node
    int min, nextNode;

    // Input number of nodes
    printf("Enter Number of Nodes : ");
    scanf("%d", &n);

    // Input cost matrix
    printf("Enter Cost Matrix:\n");

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            scanf("%d", &cost[i][j]);
        }
    }

    // Input source node
    printf("Enter Source Node : ");
    scanf("%d", &source);

    // Initialize distance and visited arrays
    for(i = 0; i < n; i++)
    {
        // Copy direct distance from source
        distance[i] = cost[source][i];

        // Initially all nodes are unvisited
        visited[i] = 0;
    }

    // Source node is visited
    visited[source] = 1;

    // Distance from source to itself = 0
    distance[source] = 0;

    // Counter for visited nodes
    int count = 1;

    // Main Dijkstra Algorithm
    while(count < n - 1)
    {
        // Assume large minimum distance
        min = 999;

        // Find nearest unvisited node
        for(i = 0; i < n; i++)
        {
            if(distance[i] < min &&
               !visited[i])
            {
                min = distance[i];

                nextNode = i;
            }
        }

        // Mark selected node as visited
        visited[nextNode] = 1;

        // Update distances of neighboring nodes
        for(i = 0; i < n; i++)
        {
            if(!visited[i])
            {
                // Check shorter path through nextNode
                if(min + cost[nextNode][i]
                   < distance[i])
                {
                    // Update shorter distance
                    distance[i] =
                    min + cost[nextNode][i];
                }
            }
        }

        // Increment count
        count++;
    }

    // Print shortest paths
    printf("\nShortest Paths:\n");

    for(i = 0; i < n; i++)
    {
        if(i != source)
        {
            printf("%d -> %d = %d\n",
                    source,
                    i,
                    distance[i]);
        }
    }

    return 0;
}