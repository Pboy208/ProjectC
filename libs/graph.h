#ifndef	_GRAPH_H_
#define	_GRAPH_H_

#include "jrb.h"
#include "jval.h"
#define INFINITY 999999
#define max_adjacent 1000

typedef struct {
    JRB edges;
    JRB vertices;
    int* E;
    int* V;
} Graph;

typedef struct region_{
    Graph region;
    int regionID;
    struct region_* next;
}*Region;

typedef struct global_{
    Region* global;
    int globalID;
    struct global_* next;
}*Global;

void printGraph(Graph g);
Graph createGraph();
void addVertex(Graph graph, int id, char* name);
char *getVertex(Graph graph, int id);
void addEdge(Graph graph, int v1, int v2,int w);
int hasEdge(Graph graph, int v1, int v2);
int indegree(Graph graph, int v, int* output);
int outdegree(Graph graph, int v, int* output);
int DAG(Graph graph);
void dropGraph(Graph graph);
int getAdjacentVertices(JRB graph, int vertex, int *output);
int DAG(Graph graph);
#endif

