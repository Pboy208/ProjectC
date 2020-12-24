#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#define max_node_local 1000
#define max_adjacent 4
#define max_weight 50
struct IPs{
    int ip1;
    int ip2;
    int ip3;
    int ip4;
    char ip[16];
};

// char* makeDBN(void)
// {
//     char last[5]=".com\0";
//     char *domainN = (char *)malloc(15*sizeof(char));
//     memset(domainN,'\0',sizeof(char)*15);
    
//     int arr[10];
//     memset(arr,0,sizeof(int)*10);

//     for(int i = 0 ; i < 10 ; i++){

//         int n = rand() % (90 - 65 + 1) + 65;
//         char tmp=(char)n;
//         strcat(domainN,&tmp);
//     }
//     strcat(domainN,last);
//     return domainN;
// }

char* makeDBIP(void)
{   
    char p[2]=".";
    struct IPs* ipN=(struct IPs*)malloc(sizeof(struct IPs));
    ipN->ip1= 116;
    ipN->ip2= rand() % (111 - 96 + 1) + 96;
    ipN->ip3= rand() % (255+ 1);
    ipN->ip4= rand() % (255+ 1);
    
    char ip1[4];
    itoa(ipN->ip1,ip1,10);
    char ip2[4];
    itoa(ipN->ip2,ip2,10);
    char ip3[4];
    itoa(ipN->ip3,ip3,10);
    char ip4[4];
    itoa(ipN->ip4,ip4,10);

    strcat(ipN->ip,ip1);
    strcat(ipN->ip,p);
    
    strcat(ipN->ip,ip2);
    strcat(ipN->ip,p);

    strcat(ipN->ip,ip3);
    strcat(ipN->ip,p);
    
    strcat(ipN->ip,ip4);
    return ipN->ip;

}

void makeW(int i,FILE *fo)
{
    // int adjacentN=rand() % (max_adjacent -2 + 1) + 2;
    int adjacentN=max_adjacent;
    fprintf(fo,"%d\t",adjacentN);
    //printf("%d\t%d\n",i,adjacentN);
    for(int j=0;j<adjacentN;j++)
    {
        int weight=rand() % (max_weight -1 + 1) + 1;
        int adjacent=-1;
        while(adjacent==i || adjacent ==-1)
            adjacent=rand() % (max_node_local-1 + 1);
        fprintf(fo,"%d\t%d\t",adjacent,weight);
        if(j==adjacentN-1)
            fprintf(fo,"\n");
    }
}

int main()
{
    FILE *fout = fopen("DB1k.txt","w+");
    FILE *fo = fopen("Weight1k.txt","w+");
    srand((int)time(0));

    // for(int i = 0; i < max_node_local; ++i){
    //     char *name = makeDBN();
    //     fprintf(fout,"%s\n",name);
    // }

    for(int i = 0; i < max_node_local; ++i){
        char *ip=makeDBIP();
        fprintf(fout,"%s\n",ip);
    }

    for(int i = 0; i < max_node_local; ++i){
        // //char *name = makeDBN();
        // char *ip=makeDBIP();
        // fprintf(fout,"%s\n",ip);
        makeW(i,fo);
        printf("%d\n",i);
    }
    fclose(fo);
    fclose(fout);
}