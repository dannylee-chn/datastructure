#include <stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include <string.h>

//第一版并查集：id+id对应集合
typedef struct{
    int* id;
    int size;
}UnionFind1 ;

UnionFind1* UF_create(int size){
    UnionFind1* uf = (UnionFind1*)malloc(sizeof(UnionFind1));
    uf->size = size;
    uf->id = (int*)malloc(sizeof(int) * size);
    for (int i=0;i<size;i++) {
        uf->id[i]=i;
    }
    return uf;
}
int getSize(UnionFind1* uf) {
    return uf->size;
}
//查找元素p对应的集合编号
int find(UnionFind1* uf,int p) {
    if (p<0||p>uf->size)perror("p is out of bound.");
    return uf->id[p];
}

//查看元素 p，q是否属于同一个集合
bool isConnected(UnionFind1* uf,int p,int q) {
    return find(uf,p)==find(uf,q);
}

//合并元素p，q所属的集合
void Union(UnionFind1* uf,int p,int q) {
    int pID=uf->id[p];
    int qID=uf->id[q];

    if (pID==qID)return;
    else {
        for (int i=0;i<uf->size;i++) {
            if (uf->id[i]==qID) {
                uf->id[i]=pID;
            }
        }
    }
}