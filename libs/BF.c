#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jval.c"
#include "jrb.c"
#include "graph.c"
#include "dllist.c"


void display(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        printf("%d\n", arr[i]);
    }
    printf("\n");
}

void Bellmanford(Graph g, int source,int destination, int **parent, int **distance)
{
    //variables
    int i, j, u, v, w;

    //total vertex in the graph g
    int tV = *g.V;
    //total edge in the graph g
    int tE = *g.E;

    //distance array
    //size equal to the number of vertices of the graph g
    int *d = (int *)malloc(sizeof(int) * tV);

    //predecessor array
    //size equal to the number of vertices of the graph g
    int *p = (int *)malloc(sizeof(int) * tV);

    //step 1: fill the distance array and predecessor array
    for (i = 0; i < tV; i++)
    {
        d[i] = INFINITY;
        p[i] = 0;
    }

    //mark the source vertex
    d[source] = 0;

    //step 2: relax edges |V| - 1 times
    for (i = 0; i < tV - 1; i++)
    {
        JRB temp1, temp2;
        jrb_traverse(temp1, g.vertices)
        {
            u = jval_i(temp1->key);
            int output[max_adjacent];
            int res = getAdjacentVertices(g.edges, u, output);
            for (int l = 0; l < res; l++)
            {
                JRB tree = jrb_find_int(g.edges, u);
                JRB tree2 = (JRB)jval_v(tree->val);
                JRB node = jrb_find_int(tree2, output[l]);
                v = output[l];
                w = jval_i(node->val);
                if (d[u] != INFINITY && d[v] > d[u] + w)
                {
                    d[v] = d[u] + w;
                    p[v] = u;
                }
            }
        }
    }

    p[source] = source;
    (*parent) = p;
    (*distance) = d;
}
