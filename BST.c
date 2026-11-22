#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int e;
    struct Node*left;
    struct Node*right;
}Node;

typedef struct BST {
    Node*root;
    int size;
}BST;

Node* create_bt_node(int e) {
    Node*node=malloc(sizeof(Node));
    node->e=e;
    node->left=NULL;
    node->right=NULL;
    return node;
}

BST* bst_create() {
    BST*bst=malloc(sizeof(BST));
    bst->root=NULL;
    bst->size=0;
    return bst;
}

int bst_get_size(BST*bst) {
    return bst->size;
}

bool bst_is_empty(BST*bst) {
    return bst->size==0;
}

//向以node为根节点的二分搜索树中插入元素e,递归算法
//返回插入新节点后二叉树的根
Node* bst_add_recursive(Node*node,int e,bool *insert_success) {
    if (node==NULL) {
        *insert_success=true;
        return create_bt_node(e);
    }
    if (e<node->e) {
        node->left=bst_add_recursive(node->left,e,insert_success);
    }
    else if (e>node->e) {
        node->right=bst_add_recursive(node->right,e,insert_success);
    }
    else {
        *insert_success = false;
    }
    return node;
}

//向二分搜索树中添加新元素e
void bst_add(BST*bst,int e) {
    bool ok = false;
    bst->root=bst_add_recursive(bst->root,e,&ok);
    if (ok) {
        bst->size ++;
    }
}

//查询：递归查询当前以node为根节点的子树中是否包含元素e
bool bst_contains_recursive(Node*node,int e) {
    if (node==NULL) {
        return false;
    }

    if (e<node->e) {
        return bst_contains_recursive(node->left,e);
    }
    else if (e>node->e) {
        return bst_contains_recursive(node->right,e);
    }
    else {
        return true;
    }
}

//查询元素：看二分搜索树中是否包含元素e
bool bst_contains(BST*bst,int e) {
    return bst_contains_recursive(bst->root,e);
}

//递归前序遍历以node为根的二分搜索树
void preOrder(Node*node) {
    if (node==NULL)return;

    printf("%d ",node->e);
    preOrder(node->left);
    preOrder(node->right);
}

//二分搜索树的前序遍历
void bst_pre_order(BST*bst) {
    preOrder(bst->root);
}

//递归中序遍历以node为根的二分搜索树
void inOrder(Node*node) {
    if (node==NULL)return;

    inOrder(node->left);
    printf("%d ",node->e);
    inOrder(node->right);
}

//二分搜索树的中序遍历
void bst_in_order(BST*bst) {
    inOrder(bst->root);
}

//递归后序遍历以node为根的二分搜索树
void postOrder(Node*node) {
    if (node==NULL)return;

    postOrder(node->left);
    postOrder(node->right);
    printf("%d ",node->e);
}

//二分搜索树的后序遍历
void bst_post_order(BST*bst) {
    postOrder(bst->root);
}

//递归找到二分搜索树最小元素
Node* minimum(Node*node) {
    if (node->left==NULL)return node;
    return minimum(node->left);
}

int bst_minimum(BST*bst) {
    if (bst->size==0) {
        printf("BST is empty.");
        return 0;
    }
    return minimum(bst->root)->e ;
}

//非递归
int minimum2(BST*bst) {
    if(bst->root == NULL) {
        assert(false);
    }
    Node*cur=bst->root;
    while (cur->left!=NULL) {
        cur=cur->left;
    }
    return cur->e;
}

//递归找到二分搜索树最小元素
Node* maxmum(Node*node) {
    if (node->right==NULL)return node;
    return maxmum(node->right);
}

int bst_maxmum(BST*bst) {
    if (bst->size==0) {
        printf("BST is empty.");
        return 0;
    }
    return maxmum(bst->root)->e ;
}

//删除以node为根的最小元素,返回新节点
Node* removeMin(Node*node) {
    if (node->left==NULL) {
        Node*rightNode=node->right;
        node->right=NULL;
        return rightNode;
    }

    node->left=removeMin(node->left);
    return node;
}

//删除最小元素,返回最小值
int bst_remove_min(BST*bst) {
    int ret=bst_minimum(bst);
    bst->root=removeMin(bst->root);
    return ret;
}

//删除以node为根的最大元素,返回新节点
Node* removeMax(Node*node) {
    if (node->right==NULL) {
        Node*leftNode=node->left;
        node->left=NULL;
        return leftNode;
    }

    node->right=removeMax(node->right);
    return node;
}

//删除最小元素,返回最小值
int bst_remove_max(BST*bst) {
    int ret=bst_maxmum(bst);
    bst->root=removeMax(bst->root);
    return ret;
}

//删除以node为根节点的二分搜索树中值为e的元素，返回删除后新根
Node*removeR(Node*node,int e) {
    if (node==NULL)return NULL;

    if (e<node->e) {
        node->left=removeR(node->left,e);
        return node;
    }
    else if (e>node->e) {
        node->right=removeR(node->right,e);
        return node;
    }
    else {//e==node.e

        if (node->left==NULL) {
            Node*rightNode=node->right;
            node->right=NULL;
            return rightNode;
        }
        if (node->right==NULL) {
            Node*leftNode=node->left;
            node->left=NULL;
            return leftNode;
        }
        //待删除左右子树均不为空，找到后继：大于待删除元素的最小节点
        Node*successor=minimum(node->right);
        successor->right=removeMin(node->right);
        successor->left=node->left;
        node->left=node->right=NULL;
        return successor;
    }
}

//删除任意节点:分类：只有左孩子/右孩子，右+左：找后继:右子树的最小值
void bst_remove(BST*bst,int e) {
    bst->root=removeR(bst->root,e);
}

int main(void) {
    BST* bst = bst_create();
    // 插入：5,3,7,2,4,6,8
    bst_add(bst,5);
    bst_add(bst,3);
    bst_add(bst,7);
    bst_add(bst,2);
    bst_add(bst,4);
    bst_add(bst,6);
    bst_add(bst,8);
    bst_add(bst,5); // 重复，不插入

    printf("size = %d\n", bst_get_size(bst));

    printf("前序：");
    bst_pre_order(bst);
    printf("\n中序：");
    bst_in_order(bst);
    printf("\n后序：");
    bst_post_order(bst);
    printf("\n");

    printf("最小值(递归) = %d\n", bst_minimum(bst));
    printf("最小值(非递归) = %d\n", minimum2(bst));
    printf("最大值 = %d\n", bst_maxmum(bst));

    printf("是否包含 4：%s\n", bst_contains(bst,4)?"true":"false");
    printf("是否包含 9：%s\n", bst_contains(bst,9)?"true":"false");

    // 删除最小值
    int delMin = bst_remove_min(bst);
    printf("删除的最小值：%d\n", delMin);
    printf("删除min后中序：");
    bst_in_order(bst);
    printf("\n");

    // 删除最大值
    int delMax = bst_remove_max(bst);
    printf("删除的最大值：%d\n", delMax);
    printf("删除max后中序：");
    bst_in_order(bst);
    printf("\n");

    return 0;
}

