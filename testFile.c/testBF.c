#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./libs/jval.c"
#include "./libs/jrb.c"
#include "./libs/graph.c"
#include "./libs/dllist.c"
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

void bellmanford(Graph g, int source,int **parent)
{
    //variables
    int i, j, u, v, w;

    //total vertex in the graph g
    int tV = *g.V;

    //total edge in the graph g
    int tE = *g.E;

    //distance array
    //size equal to the number of vertices of the graph g
     int *d = (int*)malloc(sizeof(int)*tV);

    //predecessor array
    //size equal to the number of vertices of the graph g
    int *p = (int*)malloc(sizeof(int)*tV);

    //step 1: fill the distance array and predecessor array
    for (i = 0; i < tV; i++)
    {
        d[i] = INFINITY;
        p[i] = 0;
    }

    //mark the source vertex
    d[source] = 0;
    //step 2: relax edges |V| - 1 times
    for (i = 1; i <= tV - 1; i++)
    {
        JRB temp1, temp2;
        int i = 0;
        jrb_traverse(temp1, g.vertices)
        {
            u = jval_i(temp1->key);
            int output[10];
            int res = getAdjacentVertices(g.edges, u, output);
            for (int i = 0; i < res; i++)
            {
                JRB tree = jrb_find_int(g.edges, u);
                JRB tree2 = (JRB)jval_v(tree->val);
                JRB node = jrb_find_int(tree2, output[i]);
                v = output[i];
                w = jval_i(node->val);
                 if (d[u] != INFINITY && d[v] > d[u] + w)
                {
                    d[v] = d[u] + w;
                    p[v] = u;
                }
            }
        }
    }
    //step 3: detect negative cycle
    //if value changes then we have a negative cycle in the graph
    //and we cannot find the shortest distances
    // for (i = 0; i < tE; i++)
    // {
    //     u = g->edge[i].u;
    //     v = g->edge[i].v;
    //     w = g->edge[i].w;
    //     if (d[u] != INFINITY && d[v] > d[u] + w)
    //     {
    //         printf("Negative weight cycle detected!\n");
    //         return;
    //     }
    // }

    //No negative weight cycle found!
    //print the distance and predecessor array
    // printf("Distance array: ");
    // display(d, tV);
    // printf("Predecessor array: ");
    //display(p, tV);
    (*parent)= d;

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
    bellmanford(g,7,&parent);
    for(int i=0;i<max_node;i++)
        printf("%d\t",i);
    printf("\n");
    display(parent,max_node);
}
