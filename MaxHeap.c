#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include"Array.h"

typedef struct {
    Array*data;
}MaxHeap;

MaxHeap* create_max_heap(int capacity) {
    MaxHeap*a=malloc(sizeof(MaxHeap));
    a->data=array_create(capacity);
    return a;
}

MaxHeap* create_max_heap_default() {
    MaxHeap*a=malloc(sizeof(MaxHeap));
    a->data=array_create_default();
    return a;
}

//返回堆中元素
int getsize_max_heap(MaxHeap*a) {
    return getSize(a->data);
}

//堆是否为空，返回布尔值
bool isempty_max_heap(MaxHeap*a) {
    return isEmpty(a->data);
}

//返回完全二叉树的数组表示中，index索引所表示的父亲节点元素的索引
int parent(int index) {
    if (index==0) {
        printf("index-0 doesn't have parent.");
        return -1;
    }
    return (index-1)/2;
}

//返回完全二叉树的数组表示中，index索引所表示的左孩子节点元素的索引
int leftChild(int index) {
    return index*2+1;
}

//返回完全二叉树的数组表示中，index索引所表示的右孩子节点元素的索引
int rightChild(int index) {
    return index*2+2;
}

//上浮
void siftUp(MaxHeap*a,int k) {
    while (k>0&&get(a->data,k)>get(a->data,parent(k))) {
        swap(a->data,k,parent(k));
        k = parent(k);
    }
}

//向堆中添加元素
void add_max_heap(MaxHeap*a,int e) {
    add_last(a->data,e);
    siftUp(a,getSize(a->data)-1);
}

//下沉
void siftDown(MaxHeap*a,int k) {
    while (leftChild(k)<getsize_max_heap(a)) {
        int j=leftChild(k);
        //有右孩子并且右孩子大于左孩子：完全二叉树
        if (j+1<getsize_max_heap(a)&&get(a->data,j+1)>get(a->data,j)) {
            j=rightChild(k);
        }
        //此时data[j]是k左右孩子中的最大值
       if (get(a->data,k)>=get(a->data,j)) {
           break;
       }
       swap(a->data,k,j);
        k=j;
    }
}

//看堆中最大的元素
int findmax(MaxHeap*a) {
    if (isempty_max_heap(a)) {
        printf("Cannot findmax when heap is empty");
        return -1;
    }
    return get(a->data,0);
}


//取出堆中最大元素
int extract_max(MaxHeap*a) {
    int ret=findmax(a);
    swap(a->data,0,getSize(a->data)-1);
    array_remove_last(a->data);
    siftDown(a,0);
    return ret;
}

//堆排序
void HeapSort(int*data,int dataSize) {
    MaxHeap*a=create_max_heap_default();
    for (int i=0;i<dataSize;i++) {
        add_max_heap(a,data[i]);
    }
    for (int i=dataSize-1;i>=0;i--) {
        data[i]=extract_max(a);
    }
}

//取出堆中最大元素，替换成e
int replace(MaxHeap*a,int e) {
    int ret=findmax(a);
    set(a->data,0,e);
    siftDown(a,0);
    return ret;
}

//heapify:将数组直接转换成堆
MaxHeap* heapify(int*arr,int arrSize) {
    MaxHeap*a=create_max_heap_default();
    Array*data=array_create_based_on_data(arr,arrSize);
    a->data=data;
    for (int i=parent(arrSize-1);i>=0;i--) {
        siftDown(a,i);
    }
    return a;
}

int main()
{
    printf("===== 最大堆 功能测试 =====\n");

    // 测试1：逐个add插入 & 取出
    printf("\n【测试1：add 插入】\n");
    MaxHeap *heap1 = create_max_heap_default();
    int arr_add[] = {15, 10, 20, 3, 8, 17};
    int n1 = sizeof(arr_add)/sizeof(arr_add[0]);
    for(int i = 0; i < n1; i++){
        add_max_heap(heap1, arr_add[i]);
        printf("插入 %d，当前堆顶：%d\n", arr_add[i], findmax(heap1));
    }
    printf("依次取出：");
    while(!isempty_max_heap(heap1)){
        printf("%d ", extract_max(heap1));
    }
    printf("\n");
    free(heap1->data);
    free(heap1);


    // 测试2：heapify 批量建堆
    printf("\n【测试2：heapify 批量建堆】\n");
    int arr_heapify[] = {2, 5, 1, 9, 7, 3, 6};
    int n2 = sizeof(arr_heapify)/sizeof(arr_heapify[0]);
    MaxHeap *heap2 = heapify(arr_heapify, n2);
    printf("原数组：");
    for(int i = 0; i < n2; i++) printf("%d ", arr_heapify[i]);
    printf("\n批量建堆后取出：");
    while(!isempty_max_heap(heap2)){
        printf("%d ", extract_max(heap2));
    }
    printf("\n");
    free(heap2->data);
    free(heap2);


    // 测试3：replace 替换堆顶
    printf("\n【测试3：replace 替换堆顶】\n");
    MaxHeap *heap3 = create_max_heap_default();
    add_max_heap(heap3, 10);
    add_max_heap(heap3, 6);
    add_max_heap(heap3, 8);
    printf("替换前堆顶：%d\n", findmax(heap3));
    int oldTop = replace(heap3, 2);
    printf("被替换的值：%d，替换后堆顶：%d\n", oldTop, findmax(heap3));
    printf("依次取出：");
    while(!isempty_max_heap(heap3)){
        printf("%d ", extract_max(heap3));
    }
    printf("\n");
    free(heap3->data);
    free(heap3);


    // 测试4：HeapSort 堆排序
    printf("\n【测试4：HeapSort堆排序】\n");
    int sortArr[] = {4, 2, 7, 1, 9, 3};
    int n4 = sizeof(sortArr)/sizeof(sortArr[0]);
    printf("排序前：");
    for(int i = 0; i < n4; i++) printf("%d ", sortArr[i]);
    HeapSort(sortArr, n4);
    printf("\n排序后：");
    for(int i = 0; i < n4; i++) printf("%d ", sortArr[i]);
    printf("\n");


    // 测试5：空堆边界
    printf("\n【测试5：空堆边界测试】\n");
    MaxHeap *heap4 = create_max_heap_default();
    if(isempty_max_heap(heap4)){
        printf("空堆判断：正确\n");
    }
    printf("下面两行是预期的空堆提示：\n");
    findmax(heap4);
    extract_max(heap4);
    free(heap4->data);
    free(heap4);

    return 0;
}
