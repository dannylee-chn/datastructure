#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK 100
#define max(a,b) ((a)>(b)?(a):(b))

typedef struct AVLTree {
    int val;
    int height;
    struct AVLTree *left;
    struct AVLTree *right;
}AVLTree;

typedef struct {
    AVLTree *root;
    int size;
}AVL;

AVL* bst_create(){
    AVL *tree = malloc(sizeof(AVL));
    tree->root = NULL;
    tree->size = 0;
    return tree;
}
AVLTree* node_create(int e) {
    AVLTree* newNode = malloc(sizeof(AVLTree));
    newNode->val= e;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height=1;
    return newNode;
}

int bst_get_size(AVL *tree) {
    return tree->size;
}

bool bst_isEmpty(AVL *tree) {
    return tree->size == 0;
}

void avl_inOrder(AVLTree* node,int arr[]) {
    if (node==NULL)return;

    int i=0;
    avl_inOrder(node->left,arr);
    arr[i++]=node->val;
    avl_inOrder(node->right,arr);
}

bool isBST(AVL* tree) {
    int arr[tree->size];
    avl_inOrder(tree->root,arr);
    for (int i=1;i<=tree->size;i++) {
        if (arr[i-1]>arr[i])return false;
    }
    return true;
}

int getHeight(AVLTree* node) {
    if (node==NULL)return 0;
    return node->height;
}

//获得节点node的平衡因子
int getBalanceFactor(AVLTree* node) {
    if (node==NULL)return 0;
    else {
        return getHeight(node->left)-getHeight(node->right);
    }
}

//判断以node为根的二叉树是否是一颗平衡二叉树，递归算法
bool isBalanced(AVLTree* node) {
    if (node==NULL)return true;

    int balanceFactor=getBalanceFactor(node);
    if (abs(balanceFactor)>1)return false;
    return isBalanced(node->left) && isBalanced(node->right);

}

//判断该二叉树是否是一颗平衡二叉树
bool avl_isBalanced(AVL* tree) {
    return isBalanced(tree->root);
}

//右旋转：返回新的根节点
//    y   回溯到的第一个           x
//   / \                        / \
//   x   T4    向右旋转(y)      z    y
//  / \      ----------->    / \  / \
// z   T3                 T1 T2 T3 T4
// / \
// T1  T2
AVLTree* rightRotate(AVLTree* y) {
    AVLTree* x=y->left;
    AVLTree* T3=x->right;

    //向右旋转过程
    x->right=y;
    y->left=T3;

    //更新height
    y->height=max(getHeight(y->left),getHeight(y->right))+1;
    x->height=max(getHeight(x->left),getHeight(x->right))+1;

    return x;
}
//左旋转
AVLTree* leftRotate(AVLTree* y){
    AVLTree* x=y->right;
    AVLTree* T2=x->left;
    x->left=y;
    y->right=T2;

    //更新height
    y->height=max(getHeight(y->left),getHeight(y->right))+1;
    x->height=max(getHeight(x->left),getHeight(x->right))+1;

    return x;
}

AVLTree* add(AVLTree* node,int e,AVL *tree) {
    if (node==NULL) {
        tree->size++;
        return node_create(e);
    }
    if (e<node->val) {
        node->left=add(node->left,e,tree);
    }
    else if (e>node->val) {
        node->right=add(node->right,e,tree);
    }

    //更新node的height
    node->height=max(getHeight(node->left),getHeight(node->right));
    //更新平衡因子
    int balanceFactor=getBalanceFactor(node);
    if (abs(balanceFactor)>1)printf("unbalanced:%d",balanceFactor);

    //平衡维护
    //LL
    if (balanceFactor>1&&getBalanceFactor(node->left)>=0) {//LL（左左）：左重，并且左孩子也是左重--右旋转
        return rightRotate(node);
    }
    //RR
    if (balanceFactor<-1&&getBalanceFactor(node->right)<=0) {
        return leftRotate(node);
    }

    //LR
    if (balanceFactor>1&&getBalanceFactor(node->right)<0) {
        node->left=leftRotate(node->left);
        return rightRotate(node);

    }

    //RL
    if (balanceFactor<-1&&getBalanceFactor(node->left)>0) {
        node->right=rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}
void bst_add(AVL *tree, int e) {
    tree->root=add(tree->root,e,tree);
}

bool contains(AVLTree *node,int e) {
    if (node==NULL)return false;

    if (e==node->val)return true;

    else if (e<node->val) {
        return contains(node->left,e);
    }
    else {
        return contains(node->right,e);
    }
}

bool bst_contains(int e,AVL *tree) {
    return contains(tree->root,e);
}
