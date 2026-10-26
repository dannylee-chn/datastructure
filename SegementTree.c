#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data;
    int* tree;
    int size;
} SegmentTree;

typedef enum {
    OP_SUM,
    OP_MAX,
    OP_MIN
} OpType;

SegmentTree* se_create(int arr[],int arrSize) {
    SegmentTree* st = malloc(sizeof(SegmentTree));
    st->size = arrSize;
    st->data = malloc(sizeof(int)*arrSize);
    st->tree = malloc(4*sizeof(int)*arrSize);
    for(int i=0;i<arrSize;i++){
        st->data[i] = arr[i];
    }
    return st;
}

int get(SegmentTree* st, int index) {
    if (index<0||index>st->size)perror("Index is illegal.");
    return st->data[index];
}

int getSize(SegmentTree* st) {
    return st->size;
}

int leftChild(int index) {
    return 2*index+1;
}

int rightChild(int index) {
    return 2*index+2;
}

int merge(int a, int b, OpType op) {
    switch(op) {
        case OP_SUM: return a + b;
        case OP_MAX: return a > b ? a : b;
        case OP_MIN: return a < b ? a : b;
        default: return 0;
    }
}

//递归创建线段树：根节点是两个孩子的总和
//在treeIndex位置创建表示区间[l,r]的线段树--存[l,r]的信息
void build_segementTree(SegmentTree* st,int treeIndex,int l,int r,OpType operator) {
    if (l==r) {
        st->tree[treeIndex]=st->data[l];
        return;
    }
    int leftTreeIndex=leftChild(treeIndex);
    int rightTreeIndex=rightChild(treeIndex);

    int mid=l+(r-l)/2;
    build_segementTree(st,leftTreeIndex,l,mid,operator);
    build_segementTree(st,rightTreeIndex,mid+1,r,operator);

    //如何综合：自己定义merg e方法
    st->tree[treeIndex] = merge(st->tree[leftTreeIndex], st->tree[rightTreeIndex], operator);

}

//递归函数查询:在以treeIndex为根的线段树中[l...r]的范围里，搜索区间[queryL...queryR]的值
int query(SegmentTree* st,int treeIndex,int l,int r,int queryL,int queryR, OpType op) {
    if (l == queryL && r == queryR) {
        return st->tree[treeIndex];
    }
    int mid = l + (r - l) / 2;
    int leftTreeIndex = leftChild(treeIndex);
    int rightTreeIndex = rightChild(treeIndex);

    if (queryL >= mid + 1) {
        return query(st, rightTreeIndex, mid+1, r, queryL, queryR, op);
    } else if (queryR <= mid) {
        return query(st, leftTreeIndex, l, mid, queryL, queryR, op);
    } else {
        int leftRes = query(st, leftTreeIndex, l, mid, queryL, mid, op);
        int rightRes = query(st, rightTreeIndex, mid+1, r, mid+1, queryR, op);
        return merge(leftRes, rightRes, op);
    }
}
//查询操作:返回区间[queryL,queryR]的值
int se_query(SegmentTree* st, int queryL,int queryR, OpType op) {
    if (queryL < 0 || queryL >= st->size || queryR < 0 || queryR >= st->size || queryL > queryR) {
        perror("Index is illegal.");
        exit(EXIT_FAILURE);
    }
    return query(st, 0, 0, st->size - 1, queryL, queryR, op);
}

//在以treeIndex为根的线段树中更新index的值为e
void set(SegmentTree* st,int treeIndex,int l,int r,int index,int e) {
    if (l==r) {
        st->tree[treeIndex]=e;
        return;
    }
    int mid=l+(r-l)/2;
    int leftTreeIndex=leftChild(treeIndex);
    int rightTreeIndex=rightChild(treeIndex);
    if (index>=mid+1) {
        set(st,rightTreeIndex,mid+1,r,index,e);
    }
    else {
        set(st,leftTreeIndex,l,mid,index,e);
    }
    st->tree[treeIndex]=merge(st->tree[leftTreeIndex],st->tree[rightTreeIndex],OP_SUM);
}
//更新线段树:将index位置值改成e
void se_et(SegmentTree* st,int index,int e) {
    if (index<0||index>st->size-1)perror("Index is illegal.");
    st->data[index]=e;
    set(st,0,0,st->size-1,index,e);
}

void se_free(SegmentTree* st){
    free(st->data);
    free(st->tree);
    free(st);
}

int main() {
    int nums[]={5,24,67,4,68,2,57,96,7,2};
    SegmentTree* tree=se_create(nums,10);
    build_segementTree(tree,0,0,tree->size-1,OP_SUM);
    for (int i = 0; i < 4 * tree->size; i++) {
        printf("%d ", tree->tree[i]);
    }
    printf("%d ",se_query(tree,0,2,OP_SUM));
}