#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./libs/BF.c"
#define INFINITY 999999
#define max_node 100
Graph readInput(Graph g)
{
    FILE *fin = fopen("DBlocalvnWeight.txt", "r");
    for (int i = 0; i < max_node; i++)
    {
        int adjacentN = 0;
        addVertex(g, i, "null");
        fscanf(fin, "%d\t", &adjacentN);
        for (int j = 0; j < adjacentN; j++)
        {
            int adjacent = 0, weight = 0;
            fscanf(fin, "%d\t%d\t", &adjacent, &weight);
            if ((j - 1) == adjacentN)
                fscanf(fin, "\n");
            addEdge(g, i, adjacent, weight);
        }
    }
    printGraph(g);
    fclose(fin);
    return g;
}

void printPath(int parent[], int source, int destination)
{
    printf("The path from node %d to %d:\n", source, destination);
    int b[max_node];
    int i = 0;
    b[0] = destination;
    while (parent[destination] != source)
    {
        destination = parent[destination];
        b[++i] = destination;
    }
    b[++i] = source;
    for (int j = i; j > 0; j--)
        printf("%d->", b[j]);
    printf("%d\n", b[0]);
}

void printWeight(Graph g, int v1, int v2)
{
    JRB tree, node, tmp;
    tree = jrb_find_int(g.edges, v1);
    node = (JRB)jval_v(tree->val);
    tmp = jrb_find_int(node, v2);
    printf("%d weight", jval_i(tmp->val));
}

void menu(void)
{
    printf("\n-------------------MENU-------------------\n");
    printf("1.Input Data\n");
    printf("2.Shortest Path between 2 IPs\n");
    printf("3.\n");
    printf("4.Exit\n");
}

int main()
{
    int *parent = (int *)malloc(sizeof(int) * max_node);
    Graph g = createGraph();
    int choice = 0;
    int source,destination;
    do
    {
        menu();
        scanf("%d", &choice);
        
        switch (choice)
        {
        case 1:
            readInput(g);
            system("pause");
            break;
        case 2:
            printf("Input source node:");
            scanf("%d",&source);
            printf("Input destination node:");
            scanf("%d",&destination);
            bellmanford(g, source, &parent);
            printPath(parent, source, destination);
            system("pause");
            break;
        case 4:
            printf("BAI BAI\n");
            break;
        default:
            printf("Invalid choice\n");
            break;
        }
    } while (choice != 4);
}
