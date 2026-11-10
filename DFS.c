#include "Graph.h"
#include<stdio.h>
#include <stdlib.h>

//稠密图递归dfs，求连通分量
void dfsDense(DenseGraph* g, int v, bool visited[], int id[], int ccount){
    printf("%d ", v);
    visited[v] = true;
    id[v] = ccount;
    int n = DV(g);
    for(int w = 0; w < n; w++)
    {
        if(g->matrix[v][w] == 1 && !visited[w]){
            dfsDense(g, w, visited, id, ccount);
        }
    }
}

int* dfsDenseTraverse(DenseGraph* g){
    int ccount=0;//连通分量个数
    int n = DV(g);
    int *id=(int*)malloc(sizeof(int)*n);//哪些节点是联通的：并查集
    for (int i=0;i<n;i++) {
        id[i]=-1;
    }
    bool* visited = (bool*)calloc(n, sizeof(bool));
    printf("稠密图DFS：");
    for(int i = 0; i < n; i++){
        if(!visited[i])
        {
            ccount++;
            dfsDense(g, i, visited, id, ccount);
        }
    }
    printf("\n");
    free(visited);
    return id;
}

bool isConnected(int u, int v, int id[])
{
    return id[u] == id[v];
}
