#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "dllist.h"
#include "graph.h"

Graph createGraph()
{
    Graph g;
    g.edges = make_jrb();
    g.vertices = make_jrb();
    g.E = (int *)malloc(sizeof(int));
    g.V = (int *)malloc(sizeof(int));
    *g.E = 0;
    *g.V = 0;
    return g;
}

void printGraph(Graph graph)
{
    JRB node;
    printf("Node\tAdjacents\n");
    jrb_traverse(node, graph.edges)
    {
        if (node != NULL)
        {
            int output[10];
            int res = getAdjacentVertices(graph.edges, jval_i(node->key), output);
            printf("%d\t", jval_i(node->key));
            for (int i = 0; i < res; i++)
            {
                printf("%d ", output[i]);
            }
            printf("\n");
        }
    }
    printf("Total V:%d\n", *graph.V);
    printf("Total E:%d\n", *graph.E);
}

void dropGraph(Graph graph)
{
    jrb_free_tree(graph.edges);
    jrb_free_tree(graph.vertices);
}

void addVertex(Graph g, int id, char *name)
{   

    JRB node = jrb_find_int(g.vertices, id);
    if (node == NULL) // only add new vertex
    {
        jrb_insert_int(g.vertices, id, new_jval_s(strdup(name)));
        *g.V += 1;
        // if(*g.V>6000 &&*g.V<8000)
        //     printf("%d-%d\n",id,*g.V);
    }
}

void addTable(JRB table,int id,char *name)
{
    JRB node2 = jrb_find_str(table, strdup(name));
    if (node2 == NULL) // only add new vertex
    {   
        jrb_insert_str(table, name, new_jval_i(id));
    }

}

char *getVertex(Graph graph, int id)
{
    JRB node = jrb_find_int(graph.vertices, id);
    if (node == NULL)
        return NULL;
    else
        return jval_s(node->val);
}

int adjacent(JRB graph, int v1, int v2)
{
    JRB node, tree;
    node = jrb_find_int(graph, v1);
    //printf("ok\n");
    if (node == NULL)
        return 0;
    tree = (JRB)jval_v(node->val);
    if (jrb_find_int(tree, v2) == NULL)
        return 0;
    else
        return 1;
}

void addEdge(Graph graph, int v1, int v2, int w)
{
    JRB node,node2, tree,tree2;
    if (!hasEdge(graph, v1, v2) && (!hasEdge(graph,v2,v1)))
    {
        node = jrb_find_int(graph.edges, v1);
        if (node==NULL) {
            tree = make_jrb();
            jrb_insert_int(graph.edges, v1, new_jval_v(tree));
        } else{
            tree = (JRB) jval_v(node->val);
        }

        node2 = jrb_find_int(graph.edges, v2);
        if (node2==NULL) {
            tree2 = make_jrb();
            jrb_insert_int(graph.edges, v2, new_jval_v(tree2));
        } else{
            tree2 = (JRB) jval_v(node2->val);
        }
        

        *graph.E+=1;
        jrb_insert_int(tree, v2, new_jval_i(w));
        jrb_insert_int(tree2, v1, new_jval_i(w));
    }
}

int hasEdge(Graph graph, int v1, int v2)
{
    JRB node, tree;
    node = jrb_find_int(graph.edges, v1);
    if (node == NULL)
        return 0;
    tree = (JRB)jval_v(node->val);
    if (jrb_find_int(tree, v2) == NULL)
        return 0;
    else
        return 1;
}

int indegree(Graph graph, int v, int *output)
{
    JRB tree, node;
    int total = 0;
    jrb_traverse(node, graph.edges)
    {
        tree = (JRB)jval_v(node->val);
        if (jrb_find_int(tree, v))
        {
            output[total] = jval_i(node->key);
            total++;
        }
    }
    return total;
}

int outdegree(Graph graph, int v, int *output)
{
    JRB tree, node;
    int total;
    node = jrb_find_int(graph.edges, v);
    if (node == NULL)
        return 0;
    tree = (JRB)jval_v(node->val);
    total = 0;
    jrb_traverse(node, tree)
    {
        output[total] = jval_i(node->key);
        total++;
    }
    return total;
}

int getAdjacentVertices(JRB graph, int vertex, int *output)
{
    if (jrb_find_int(graph, vertex) == NULL)
        return 0;
    JRB node = jrb_find_int(graph, vertex);
    JRB tree = (JRB)jval_v(node->val);
    JRB temp;
    int i = 0;
    jrb_traverse(temp, tree)
    {
        output[i++] = jval_i(temp->key);
    }
    return i;
}

int DAG(Graph graph)
{
    if ((jrb_find_int(graph.vertices, 1)) == NULL)
    {
        printf("The node is not exist\n");
        exit(0);
    }
    Dllist node;
    Dllist stack = new_dllist();
    int *visited = (int *)calloc(sizeof(int), 7);
    int cur = 0, adjacentN = 0, adjacentVal = 0;
    dll_append(stack, new_jval_i(1));
    while (dll_empty(stack) != 1)
    {
        node = dll_last(stack);
        cur = jval_i(node->val);
        dll_delete_node(node);
        if (!visited[cur])
        {
            //printf("get into %d:",cur);
            visited[cur] = 1;
            int output[7];
            adjacentN = getAdjacentVertices(graph.edges, cur, output);
            //printf("%d:",adjacentN);
            for (int i = 0; i < adjacentN; i++)
            {

                adjacentVal = output[i];
                //printf("%d,",adjacentVal);
                dll_append(stack, new_jval_i(adjacentVal));
            }
            //printf("cut\n");
        }
        else
            return 1; // co cycle
    }
    return 0;
}