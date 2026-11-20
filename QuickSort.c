#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include"time.h"

void swap(int*arr,int l,int r) {
    int temp=arr[l];
    arr[l]=arr[r];
    arr[r]=temp;
}

void InsertionSort2(int*arr,int l,int r) {
    for (int i=l;i<=r;i++) {
        //将arr[i]放到合适位置
        int temp=arr[i];
        int j;
        for (j=i;j>l&&arr[j-1]>temp;j--) {
            arr[j]=arr[j-1];
        }
        arr[j]=temp;
    }
}

int partition(int*arr,int l,int r,int rnd) {
    int randIdx = l + rnd% (r - l + 1);
    swap(arr, l, randIdx);
    int sign = arr[l];
    int j = l, i = l;
    for (;i<=r;i++) {
        //arr[l+1,j]<v arr[j+1,i-1]>v 每次处理arr[i]的元素
        if (arr[i]<sign) {
            j++;
            swap(arr,i,j);
        }
    }
    swap(arr,l,j);
    return j;
}

void sort(int*arr,int l,int r,int rnd) {
    if (r-l<=15) {
        InsertionSort2(arr,l,r);
        return;
    }

    int p = partition(arr, l, r,rnd);
    sort(arr, l, p-1,rnd);
    sort(arr, p+1, r,rnd);
}

void QuickSort(int*arr,int arrSize) {
    int rnd=rand();
    sort(arr,0,arrSize-1,rnd);
}

//双路快排
int partition2(int*arr,int l,int r,int rnd) {
    int randIdx = l + rnd% (r - l + 1);
    swap(arr, l, randIdx);
    int sign = arr[l];

    //arr[l+1,i-1]<=v arr[j+1,r]>=v
    int i=l+1,j=r;
    while (true) {
        while (i<=j&&arr[i]<sign) {
            i++;
        }
        while (j>=i&&arr[j]>sign) {
            j--;
        }
        if (i>=j)break;
        swap(arr,i,j);
        i++;
        j--;
    }
    swap(arr,l,j);
    return j;
}

void sort2ways(int*arr,int l,int r,int rnd) {
    if (r-l<=15) {
        InsertionSort2(arr,l,r);
        return;
    }

    int p = partition2(arr, l, r,rnd);
    sort2ways(arr, l, p-1,rnd);
    sort2ways(arr, p+1, r,rnd);
}

void QuickSort2ways(int*arr,int arrSize) {
    int rnd=rand();
    sort2ways(arr,0,arrSize-1,rnd);
}

//三路快排
void partition3(int*arr,int l,int r,int rnd,int*lt,int*gt) {
    int randIdx = l + rnd% (r - l + 1);
    swap(arr, l, randIdx);
    int sign = arr[l];

    //arr[l+1,lt]<v arr[lt+1,i-1]=v arr[gt,r]>v
    *lt=l;
    *gt=r;
    int i=l+1;
    while (i< *gt) {
        if (arr[i]<sign) {
            (*lt)++;
            swap(arr,i,*lt);
            i++;
        }
        else if (arr[i]>sign) {
            (*gt)--;
            swap(arr,i,*gt);
        }
        else {
            i++;
        }
    }
    swap(arr,l,*lt);
    //arr[l,lt-1]<v arr[lt,gt -1]=v arr[gt,r]>v
}

void sort3ways(int*arr,int l,int r,int rnd) {
    if (r-l<=15) {
        InsertionSort2(arr,l,r);
        return;
    }
    int lt, gt;
    partition3(arr, l, r,rnd,&lt,&gt);
    sort3ways(arr, l, lt-1,rnd);
    sort3ways(arr, gt, r,rnd);
}

void QuickSort3ways(int*arr,int arrSize) {
    int rnd=rand();
    sort3ways(arr,0,arrSize-1,rnd);
}

int* generateOrderedArray(int n) {
    int*arr=(int*)malloc(sizeof(int)*n);
    for (int i=0;i<n;i++) {
        arr[i]=i;
    }
    return arr;
}

int* generateRandomArray(int n,int bound) {
    int*arr=(int*)malloc(sizeof(int)*n);
    for (int i=0;i<n;i++) {
        arr[i]=rand()%bound;
    }
    return arr;
}

int* generateRepeatArray(int n)
{
    int* arr = (int*)malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++)
    {
        // 前一半固定为 5，后一半随机，重复度极高
        if(i < n / 2)
            arr[i] = 5;
        else
            arr[i] = rand() % 10;
    }
    return arr;
}

#include <stdio.h>
int main() {
    srand((unsigned)time(NULL));
    int n=100000 ;
    int* a = generateRepeatArray(n);       // 大量重复元素测试

    int* a2 = (int*)malloc(sizeof(int)*n);
    int* a3 = (int*)malloc(sizeof(int)*n);
    for(int i = 0; i < n; i++)
    {
        a2[i] = a[i];
        a3[i] = a[i];
    }

    clock_t start = clock();
    QuickSort(a, n);
    clock_t end = clock();
    printf("单路快排 time: %.6f s\n", (double)(end-start)/CLOCKS_PER_SEC);
    free(a);

    clock_t start2 = clock();
    QuickSort2ways(a2, n);
    clock_t end2 = clock();
    printf("双路快排 time: %.6f s\n", (double)(end2-start2)/CLOCKS_PER_SEC);
    free(a2);

    clock_t start3 = clock();
    QuickSort3ways(a3, n);
    clock_t end3 = clock();
    printf("三路快排 time: %.6f s\n", (double)(end3-start3)/CLOCKS_PER_SEC);
    free(a3);

    return 0;
}