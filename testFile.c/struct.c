#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./libs/BF.c"
#define INFINITY 999999
#define max_node 12
void display(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        printf("%d\t", arr[i]);
    }
    printf("\n");
}

int main()
{
    int *parent=(int*)malloc(sizeof(int)*max_node);
    Graph g = createGraph();
    addVertex(g, 0, "zero");
    addVertex(g, 1, "one");
    addVertex(g, 2, "two");
    addVertex(g, 3, "three");
    addVertex(g, 4, "four");
    addVertex(g, 5, "five");
    addVertex(g, 6, "six");
    addVertex(g, 7, "seven");
    addVertex(g, 8, "eight");
    addVertex(g, 9, "nine");
    addVertex(g, 10, "ten");
    addVertex(g, 11, "eleven");
    addEdge(g, 7, 10, 6);
    addEdge(g, 10, 5, 7);
    addEdge(g, 10, 1, 11);
    addEdge(g, 5, 9, 1);
    addEdge(g, 1, 0, 8);
    addEdge(g, 9, 0, 2);
    addEdge(g, 0, 4, 2);
    addEdge(g, 0, 3, 5);
    addEdge(g, 4, 3, 1);
    addEdge(g, 3, 2, 6);
    addEdge(g, 2, 8, 10);
    addEdge(g, 2, 11, 7);
    addEdge(g, 8, 11, 10);
    addEdge(g, 10, 6, 11);
    addEdge(g, 6, 1, 3);

    printGraph(g);
    bellmanford(g,0,&parent);
    for(int i=0;i<max_node;i++)
        printf("%d\t",i);
    printf("\n");
    display(parent,max_node);
}
