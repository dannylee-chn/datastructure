#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int*data;
    int capacity;//初始化大小，最多能装的空间
    int size;//实际大小&第一个没有元素的索引
}Array;

//构造函数
Array* array_create(int capacity) {
    Array*arr=(Array*)malloc(sizeof(Array));
    arr->data=(int*)malloc(sizeof(int)*capacity);
    arr->capacity=capacity;
    arr->size=0;
    return arr;
}

//用户未传入capacity
Array* array_create_default(void) {
    return array_create(10);
}

//用户传入静态数组
Array* array_create_based_on_data(int*data,int dataSize) {
    Array* arr = array_create(dataSize);
    memcpy(arr->data, data, dataSize * sizeof(int));
    arr->size = dataSize;
    return arr;
}

//获取数组中的元素个数
int getSize(Array*arr) {
    return arr->size;
}

//获取数组中的容量
int getCapacity(Array*arr) {
    return arr->capacity ;
}

//数组是否为空
bool isEmpty(Array*arr) {
    return arr->size==0;
}

//动态数组
void array_resize(Array*arr,int new_capacity) {
    int*res=(int*)malloc(sizeof(int)*new_capacity);
    for (int i=0;i<arr->size;i++) {
        res[i]=arr->data[i];
    }
    free(arr->data);
    arr->data = res;
    arr->capacity = new_capacity;
}

//向指定索引index添加元素e
void array_insert(Array*arr,int e,int index) {
    if (index<0||index>arr->size) {//不是紧密排列
        fprintf(stderr, "array_insert error: illegal index");
        return;
    }
    if (arr->size==arr->capacity) {
        array_resize(arr,2*arr->capacity);
    }
    else {
        for (int i=arr->size-1;i>=index;i--) {
            arr->data[i+1]=arr->data[i];
        }
        arr->data[index]=e;
        arr->size++;
    }
}

//向所有元素的最后添加元素:复用insert方法
void add_last(Array*arr,int e) {
    array_insert(arr,e,arr->size);
}

//向所有元素的头添加元素:复用insert方法
void add_first(Array*arr,int e) {
    array_insert(arr,e,0);
}

//打印数组
void array_print(Array*arr) {
    printf("Array: size = %d , capacity = %d\n", arr->size, arr->capacity);
    putchar('[');
    for (int i = 0; i < arr->size; i++)
    {
        printf("%d", arr->data[i]);
        if (i != arr->size - 1)
        {
            printf(", ");
        }
    }
    putchar(']');
    putchar('\n');
}

//获取index索引元素
int get(Array*arr,int index) {
    if (index<0||index>arr->size) {//不是紧密排列
        fprintf(stderr, "get error: illegal index");
        return -1;
    }
    return arr->data[index];
}

//更新index索引元素为e
void set(Array*arr,int index,int e) {
    if (index<0||index>arr->size) {//不是紧密排列
        fprintf(stderr, "get error: illegal index");
        return;
    }
    arr->data[index]=e;
}

//查找数组中是否存在元素e
bool contains(Array*arr,int e) {
    for (int i=0;i<arr->size;i++) {
        if (arr->data[i]==e)return true;
    }
    return false;
}

//查找元素e对应的索引
int find(Array*arr,int e) {
    for (int i=0;i<arr->size;i++) {
        if (arr->data[i]==e)return i;
    }
    return -1;
}

//删除index位置元素
int array_remove(Array*arr,int index) {
    if (index<0||index>arr->size) {//不是紧密排列
        fprintf(stderr, "array_delete error: illegal index");
        return -1;
    }
    else {
        int ret=arr->data[index];
        for (int i=index+1;i<arr->size;i++) {
            arr->data[i-1]=arr->data[i];
        }
        arr->size--;
        if (arr->size==arr->capacity/4&&arr->capacity/2!=0) {
            array_resize(arr,arr->capacity/2);
        }
        return ret;
    }
}

//删除头元素
int array_remove_first(Array*arr) {
    return array_remove(arr,0);
}

//删除尾元素
int array_remove_last(Array*arr) {
    return array_remove(arr,arr->size-1);
}

//删除某个元素
void array_remove_element(Array*arr,int e) {
    int index=find(arr,e);
    if (index!=-1) {
        array_remove(arr,index);
    }
}


void array_destroy(Array* arr){
    if(arr == NULL) return;
    free(arr->data);
    free(arr);
}
