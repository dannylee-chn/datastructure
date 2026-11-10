#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include"Graph.h"

DenseGraph* createDenseGraph(int n,bool isdirected) {
    DenseGraph*g=(DenseGraph*)malloc(sizeof(DenseGraph));
    g->n=n;
    g->m=0;
    g->is_directed=isdirected;
    g->matrix=(int**)malloc(sizeof(int *)*n);
    for(int i = 0; i < n; i++){
        g->matrix[i] = (int*)malloc(n * sizeof(int));
        for(int j = 0; j < n; j++){
            g->matrix[i][j] = 0;
        }
    }
    return g;
}

int DV(DenseGraph*g) {
    return g->n;
}

int DE(DenseGraph*g) {
    return g->m;
}

bool hasEdge(DenseGraph*g,int v,int w) {
    assert(v>=0&&v<DV(g));
    assert(w>=0&&w<DV(g));

    return g->matrix[v][w];
}

void DaddEdge(DenseGraph*g,int v,int w) {
    assert(v>=0&&v<DV(g));
    assert(w>=0&&w<DV(g));

    if (hasEdge(g,v,w))return;

    g->matrix[v][w]=true;
    if (!g->is_directed) {
        g->matrix[w][v]=true;
    }
    g->m++;
}



// 创建稀疏图
SparseGraph* createSparseGraph(int n, bool isdirected) {
    SparseGraph *g = (SparseGraph*)malloc(sizeof(SparseGraph));
    g->n = n;
    g->m = 0;
    g->is_directed = isdirected;

    g->adjList = (AdjNode**)malloc(sizeof(AdjNode*) * n);
    for (int i = 0; i < n; i++) {
        g->adjList[i] = NULL;
    }
    return g;
}

int SV(SparseGraph*g) {
    return g->n;
}

int SE(SparseGraph*g) {
    return g->m;
}

bool ShasEdge(SparseGraph *g, int v, int w){
    assert(v >= 0 && v < SV(g));
    assert(w >= 0 && w < SV(g));

    AdjNode *cur = g->adjList[v];
    while(cur != NULL)
    {
        if(cur->v == w)
            return true;
        cur = cur->next;
    }
    return false;
}

void SaddEdge(SparseGraph*g,int v,int w) {
    assert(v>=0&&v<SV(g));
    assert(w>=0&&w<SV(g));

    //头插法：
    AdjNode *newNode = (AdjNode*)malloc(sizeof(AdjNode));
    newNode->v = w;
    newNode->next = g->adjList[v];
    g->adjList[v] = newNode;

    // 无向图，反向再加一条边
    if (!g->is_directed) {
        AdjNode *newNode2 = (AdjNode*)malloc(sizeof(AdjNode));
        newNode2->v = v;
        newNode2->next = g->adjList[w];
        g->adjList[w] = newNode2;
    }
    g->m++;
}

DenseGraph* readDenseGraph(const char* filename,bool isdirected) {
    FILE*fp=fopen(filename,"r");
    if (!fp)return NULL;
    int n,m;
    fscanf(fp,"%d %d",&n,&m);
    DenseGraph*g=createDenseGraph(n,isdirected);
    int v,w;
    for (int i=0;i<m;i++) {
        fscanf(fp, "%d %d", &v, &w);
        DaddEdge(g, v, w);
    }
    fclose(fp);
    return g;
}

void writeDenseMatrixToFile(DenseGraph* g, const char* filename)
{
    FILE* fp = fopen(filename, "w");
    if(fp == NULL) return;
    int n = DV(g);
    fprintf(fp, "邻接矩阵 %d*%d\n", n, n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            fprintf(fp, "%d ", g->matrix[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}
void freeDenseGraph(DenseGraph* g)
{
    if(g == NULL) return;
    for(int i = 0; i < g->n; i++)
    {
        free(g->matrix[i]);
    }
    free(g->matrix);
    free(g);
}

int main() {
    DenseGraph* g = readDenseGraph("/Users/dannyLee/Graph/testG1.txt", false);
    if(g == NULL)
    {
        printf("read graph failed\n");
        return -1;
    }
    writeDenseMatrixToFile(g, "matrix.txt");
    freeDenseGraph(g);
    return 0;
}