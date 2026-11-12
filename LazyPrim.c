#include"Graph.h"
#include"MinHeap.h"

typedef struct {
    Edge** mst;
    int mstWeight;
    int edgeCount;
} MST;


MST* LazyPrimMST(SparseGraph* g) {
    int n = g->n;
    bool* marked = calloc(n, sizeof(bool));
    DynArray* heap = da_create();

    MST* res = malloc(sizeof(MST));
    res->mst = malloc((n - 1) * sizeof(Edge*));
    res->mstWeight = 0;
    res->edgeCount = 0;

    marked[0] = true;
    // 起点0所有邻边入堆
    AdjNode* p = g->adjList[0];
    while (p != NULL) {
        Edge* e = p->edge;
        add_min(heap, e);
        p = p->next;
    }

    while (!isEmpty(heap) && res->edgeCount < n - 1) {
        Edge* e = extractMin(heap);

        // 两边都标记了，这条边是无效的，跳过
        if (marked[e->a] && marked[e->b]) {
            continue;
        }

        // 选中这条边加入MST
        res->mst[res->edgeCount++] = e;
        res->mstWeight += e->weight;

        int newNode;
        if (marked[e->a]) {
            newNode = e->b;
        } else {
            newNode = e->a;
        }
        marked[newNode] = true;
        
        // 遍历新顶点 newNode 的邻接链表，全部入堆
        AdjNode* ptr = g->adjList[newNode];
        while (ptr != NULL) {
            Edge* ne = ptr->edge;
            add_min(heap, ne);
            ptr = ptr->next;
        }
    }

    da_destroy(heap);
    free(marked);
    return res;
}