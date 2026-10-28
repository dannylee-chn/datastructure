//第六版优化：实现更彻底的路径压缩
#include <stdbool.h>
#include<stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int* parent;
    int size;
    int* rank;//rank[i]表示以i为根的集合中树的层数
}UnionFind6;

UnionFind6* uf6_create(int size) {
    UnionFind6* uf5=(UnionFind6*)malloc(sizeof(UnionFind6));
    uf5->size=size;
    uf5->parent=(int*)malloc(sizeof(int) * size);
    uf5->rank=(int*)malloc(sizeof(int) * size);
    for (int i=0;i<size;i++) {
        uf5->parent[i]=i;
        uf5->rank[i]=1;
    }
    return uf5;
}

int getSize6(UnionFind6* uf3) {
    return uf3->size;
}

//寻找根节点,O(h)复杂度，h为树的高度
int find6(UnionFind6* uf4,int p) {
    if (p<0||p>uf4->size)perror("p is out of bound.");
    if(p!=uf4->parent[p]) {
        uf4->parent[p]=find6(uf4,uf4->parent[p]);//路径压缩：递归函数，让节点直接指向根节点
    }
    return uf4->parent[p];
}

bool isConnected6(UnionFind6* uf4,int p,int q) {
    return find6(uf4,p)==find6(uf4,q);
}

void unionElement6(UnionFind6* uf4,int p,int q) {
    int pRoot=find6(uf4,p);
    int qRoot=find6(uf4,q);
    if (pRoot==qRoot)return;
    else {
        //根据两个元素所在树的rank不同判断合并方向
        //将rank低的集合合并到rank高的集合上
        if (uf4->rank[pRoot]<uf4->rank[qRoot]) {
            uf4->parent[pRoot]=qRoot;
        }
        else if (uf4->rank[pRoot]>uf4->rank[qRoot]) {
            uf4->parent[qRoot]=pRoot;
        }
        else {//==
            uf4->parent[qRoot]=pRoot;
            uf4->rank[pRoot]+=1;
        }

    }
}