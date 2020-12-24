#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./libs/BF.c"
#include "./libs/tree.c"
#define INFINITY 999999
#define max_node 10000
char weightfile[]="WeightBackup.txt";
char dbfile[]="DB.txt";
char sortedwfile[]="SortedWeight.txt";

Graph g;
tree table;

Graph readWeight(Graph g)
{
    // FILE *fin = fopen("WeightBackup.txt", "r");
    FILE *fin = fopen(weightfile, "r");    
    if(fin==NULL)
    {
        printf("Can not open %s\n",weightfile);
        exit(0);
    }
    for (int i = 0; i < max_node; i++)
    {
        int adjacentN = 0;
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
    //printGraph(g);
    fclose(fin);
    return g;
}

Graph readIp(Graph g)
{
    // FILE *fin2 = fopen("DB.txt", "r");
    FILE *fin2 = fopen(dbfile, "r");
    if(fin2==NULL)
    {
        printf("Can not open %s\n",sortedwfile);
        exit(0);
    }
    while (!feof(fin2))
    {
        int Num = 0;
        char IP[16];
        fscanf(fin2, "%d\t%s\n", &Num, IP);
        addVertex(g, Num, IP);
    }
    fclose(fin2);
    return g;
}

tree readTable(tree table)
{
    //FILE *fin2 = fopen("DB.txt", "r");
    FILE *fin2 = fopen(dbfile, "r");
    if(fin2==NULL)
    {
        printf("Can not open %s\n",dbfile);
        exit(0);
    }
    while (!feof(fin2))
    {
        mapping tmp;
        tmp.value = 0;
        fscanf(fin2, "%d\t%s\n", &tmp.value, tmp.key);
        table = insertBST(table, tmp);
        //printf("%d %s\n",table->data.value,table->data.key);
    }
    fclose(fin2);
    return table;
}

int toID(char *string, tree table)
{
    tree tmp = searchBST(table, string);
    return tmp->data.value;
}

void printPath(int parent[], int source, int destination)
{
    printf("\nThe path from node %d to %d is:\n", source, destination);
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

int menu(void)
{
    int choice = 0;
    printf("\n-------------------MENU-------------------\n");
    printf("1.Input Data\n");
    printf("2.Shortest Path between 2 IPs\n");
    printf("3.Find weight to all other IPs and Sort\n");
    printf("4.Exit\n");
    scanf("%d", &choice);
    return choice;
}

void task1(void);
int* task2(int parent[]);
void task3(int parent[]);

int main()
{
    int *parent = (int *)malloc(sizeof(int) * max_node);
    g = createGraph();
    table = createNullTree();
    int choice = 0;
    do
    {
        choice = menu();

        switch (choice)
        {
        case 1:
            task1();
            system("pause");
            break;
        case 2:
            parent=task2(parent);
            system("pause");
            break;
        case 3:
            task3(parent);
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

void task1(void)
{
    readIp(g);
    table = readTable(table);
    readWeight(g);
    printf("The total number of IPs:%d\n", sizeOfTree(table));
}

int* task2(int parent[])
{
    char s[16], d[16];
    int source, destination;
    printf("Input source node:");
    fflush(stdin);
    gets(s);
    printf("Input destination node:");
    gets(d);
    printf("Please wait for a few minutes,the program is progressing\n");

    source = toID(s, table);
    destination = toID(d, table);

    bellmanford(g, source, &parent);
    printPath(parent, source, destination);
    return parent;
}

void task3(int parent[])
{
    FILE *output=fopen(sortedwfile,"w+");
    if(output==NULL)
    {
        printf("Can not open %s\n",sortedwfile);
        exit(0);
    }
}
