#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jval.h"
#include "jrb.h"
#include "graph.h"
#include "dllist.h"


void displayDJK(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		printf("%d\t%d\n",i,arr[i]);
	}
	printf("\n");
}

int weight(Graph g, int parent, int cur)
{
	JRB tmp, tmp2;
	jrb_traverse(tmp, g.edges)
	{
		if (jval_i(tmp->key) == parent)
		{
			JRB tree = (JRB)jval_v(tmp->val);
			jrb_traverse(tmp2, tree)
			{
				if (jval_i(tmp2->key) == cur)
				{
					return jval_i(tmp2->val);
				}
			}
		}
	}
}

int minDistance(int d[], int visited[])
{
	int min = INFINITY;
	for (int i = 0; i < max_adjacent; i++)
	{	
		//printf("min %d - d %d - visited %d\n",min,d[i],visited[i]);
		if (d[i] < min && visited[i] != 1)
			min = d[i];
	}
	for(int i=0;i<max_adjacent;i++)
		if(d[i]==min)
			return i;
	
}

void Dijkstra(Graph g, int source, int destination, int *parent)
{
	//variables
	int i, j, u, v, w;
	printf("ok\n");
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

	int *visited = (int *)calloc(sizeof(int), tV);
	int cur=source, n, adjacent;
	visited[source]=1;
	for(int i=0;i<tV-1;i++)
	{
		int output2[max_adjacent];
		n = getAdjacentVertices(g.edges, cur, output2);
		for (int i = 0; i < n; i++)
		{
			adjacent = output2[i];
			//if (visited[adjacent] != 1)
			//{
				int newDistance= weight(g, cur, adjacent) + d[cur]; //cost cua node adjacent = cost tu node cur->adjacent + cost cua node cur;
				if(newDistance<d[adjacent])
					d[adjacent]=newDistance;
				parent[adjacent] = cur;
			//}
		}
		// if(i<200 && i>100)
		// {
		// 	for(int j=0;j<max_adjacent;j++)
		// 		printf("%d\t",d[j]);
		// 	printf("\n");
		// }
		cur=minDistance(d,visited);
		visited[cur]=1;
	}
	displayDJK(d,tV);
}
