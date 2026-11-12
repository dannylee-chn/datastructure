#include"UnionFind.h"
#include"Graph.h"
#include"MinHeap.h"

typedef struct {
    Edge** mst;
    int mstWeight;
    int edgeCount;
} MST;

//对所有的边进行排序:堆排序
MST* KruskalMST(SparseGraph*g){
    int n = g->n;
    MST* res = malloc(sizeof(MST));
    res->mst = malloc((n - 1) * sizeof(Edge*));
    res->mstWeight = 0;
    res->edgeCount = 0;
    DynArray* heap=(DynArray*)malloc(sizeof(DynArray));
    for (int i=0;i<n;i++) {
        AdjNode*cur=g->adjList[i];
        while (cur->next!=NULL) {
            if (cur->next->edge->a<cur->next->edge->b) {
                //无向图避免重复
                add_min(heap,cur->edge);
            }
            cur=cur->next;
        }
    }
    //是否形成环的比较
    UnionFind6* uf=uf6_create(n);
    while (!isEmpty(heap)&&res->edgeCount<g->n-1) {
        Edge*e=extractMin(heap);
        if (isConnected6(uf,e->a,e->b))
            continue;
        unionElement6(uf, e->a, e->b);
        res->mst[res->edgeCount] = e;
        res->mstWeight += e->weight;
        res->edgeCount ++;
    }
    da_destroy(heap);
    return res;

}
