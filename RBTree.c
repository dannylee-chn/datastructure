#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_STACK 100
#define RED 1
#define BLACK 0

typedef struct RBTNode {
    int val;
    struct RBTNode *left;
    struct RBTNode *right;
    bool color;
}RBTNode;

typedef struct {
    RBTNode *root;
    int size;
}RBT;

RBT* rbt_create(){
    RBT *tree = malloc(sizeof(RBT));
    tree->root = NULL;
    tree->size = 0;
    return tree;
}
RBTNode* node_create(int e) {
    RBTNode* newNode = malloc(sizeof(RBTNode));
    newNode->val= e;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->color=RED;
    return newNode;
}

int rbt_get_size(RBT *tree) {
    return tree->size;
}

bool rbt_isEmpty(RBT *tree) {
    return tree->size == 0;
}

//判断node节点颜色
bool isRed(RBTNode* node) {
    if (node==NULL)return BLACK;
    return node->color;
}

//左旋转：
//        node                      x
//       /    \                   /   \
//      T1     x      ---->    node   T3
//            / \             /   \
//           T2  T3          T1    T2

RBTNode* leftRotate(RBTNode* node) {
    RBTNode* x=node->right;
    node->right=x->left;
    x->left=node;
    x->color=node->color;
    node->color=RED;
    return x;
}

//右旋转
RBTNode* rightRotate(RBTNode* node) {
    RBTNode* x=node->left;
    node->left=x->right;
    x->right=node;
    x->color=node->color;
    node->color=RED;

    return x;
}

//向3节点添加元素--->颜色翻转
void flipColors(RBTNode* node) {
    node->color=RED;
    node->left->color=BLACK;
    node->right->color=BLACK;
}

//向以node为根的红黑树中添加元素，递归算法
//返回插入新节点后红黑树的根
RBTNode* add(RBTNode* node,int e,RBT *tree) {
    if (node==NULL) {
        tree->size++;
        return node_create(e);//默认插入红色节点
    }
    if (e<node->val) {
        node->left=add(node->left,e,tree);
    }
    else if (e>node->val) {
        node->right=add(node->right,e,tree);
    }
    //红黑树性质维护
    if (isRed(node->right)&&!isRed(node->left))
        node=leftRotate(node);

     if (isRed(node->left)&&isRed(node->left->left))
         node=rightRotate(node);

    if (isRed(node->left)&&isRed(node->right))
        flipColors(node);

    return node;
}
void rbt_add(RBT *tree, int e) {
    tree->root=add(tree->root,e,tree);
    tree->root->color=BLACK;//最终根节点为黑色
}

bool contains(RBTNode *node,int e) {
    if (node==NULL)return false;

    if (e==node->val)return true;

    else if (e<node->val) {
        return contains(node->left,e);
    }
    else {
        return contains(node->right,e);
    }
}

bool rbt_contains(int e,RBT *tree) {
    return contains(tree->root,e);
}

int main() {
    RBT *tree = rbt_create();

    int arr[] = {37, 12, 42};
    int n = sizeof(arr)/sizeof(arr[0]);
    for(int i = 0; i < n; i++){
        rbt_add(tree, arr[i]);
    }

    printf("size = %d\n", rbt_get_size(tree));
    printf("contains 12? %s\n", rbt_contains(12,tree) ? "yes" : "no");
    printf("contains 37? %s\n", rbt_contains(37,tree) ? "yes" : "no");
    printf("contains 42? %s\n", rbt_contains(42,tree) ? "yes" : "no");
    printf("contains 99? %s\n", rbt_contains(99,tree) ? "yes" : "no");


    RBT *t2 = rbt_create();
    int N = 10000;
    clock_t start = clock();

    for(int i = 0; i < N; i++){
        rbt_add(t2, i);
    }

    for(int i = 0; i < N; i++){
        rbt_contains(i, t2);
    }

    clock_t end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\n插入+查询 %d 个元素耗时：%.4f s\n", N, time);
    printf("t2 size = %d\n", rbt_get_size(t2));

    return 0;
}
