#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void InsertionSort2(int*arr,int arrSize,int l,int r) {
    for (int i=l;i<=r;i++) {
        //将arr[i]放到合适位置
        int temp=arr[i];
        int j;
        for (j=i;j-1>=l&&arr[j-1]>temp;j--) {
            arr[j]=arr[j-1];
        }
        arr[j]=temp;
    }
}


//归并过程:合并两个有序区间arr[l,mid]和arr[mid+1,r]
void merge(int*arr,int l,int mid,int r) {
    int*temp=(int*)malloc(sizeof(int)*(r-l+1));
    for (int i=0,m=l;i<r-l+1,m<=r;i++,m++) {
        temp[i]=arr[m];
    }
    int i=l,j=mid+1;
    //每轮将arr[k]赋值
    for (int k=l;k<=r;k++) {
        if (i>mid) {
            arr[k]=temp[j-l];
            j++;
        }
        else if (j>r) {
            arr[k]=temp[i-l];
            i++;
        }
        else if (temp[i-l]<temp[j-l]) {
            arr[k]=temp[i-l];
            i++;
        }
        else {
            arr[k]=temp[j-l];
            j++;
        }
    }
    free(temp);
}


//递归函数：对arr的[l,r]区间进行排序
void MergeSort(int*arr,int l,int r) {
    if (l>=r)return;

    int mid=l+(r-l)/2;
    MergeSort(arr,l,mid);
    MergeSort(arr,mid+1,r);
    if (arr[mid]>arr[mid+1]) {
        merge(arr,l,mid,r);
    }
}

//递归函数：对arr的[l,r]区间进行排序
void MergeSort2(int*arr,int l,int r) {
    if (l>=r)return;

    int mid=l+(r-l)/2;
    MergeSort2(arr,l,mid);
    MergeSort2(arr,mid+1,r);
    if (arr[mid]>arr[mid+1]) {
        merge(arr,l,mid,r);
    }
}

void MergeSort3(int*arr,int l,int r) {

    if (r-l<=15){
        InsertionSort2(arr,r-l+1,l,r);
        return;
    }

    int mid=l+(r-l)/2;
    MergeSort2(arr,l,mid);
    MergeSort2(arr,mid+1,r);
    merge(arr,l,mid,r);
}

void sort(int*arr,int arrSize) {
    MergeSort(arr,0,arrSize-1);
}
void sort2(int*arr,int arrSize) {
    MergeSort2(arr,0,arrSize-1);
}
void sort3(int*arr,int arrSize) {
    MergeSort3(arr,0,arrSize-1);
}

void merge4(int* arr, int* temp, int l, int mid, int r)
{
    for (int k = l; k <= r; k++)
    {
        temp[k] = arr[k];
    }
    int i = l;
    int j = mid + 1;
    for (int k = l; k <= r; k++)
    {
        if (i > mid)
        {
            arr[k] = temp[j++];
        }
        else if (j > r)
        {
            arr[k] = temp[i++];
        }
        else if (temp[i] < temp[j])
        {
            arr[k] = temp[i++];
        }
        else
        {
            arr[k] = temp[j++];
        }
    }
}

void MergeSort4(int* arr, int* temp, int l, int r)
{
    if (l >= r)
        return;
    int mid = l + (r - l) / 2;
    MergeSort4(arr, temp, l, mid);
    MergeSort4(arr, temp, mid + 1, r);
    merge4(arr, temp, l, mid, r);
}

// temp只在这里malloc一次
void sort4(int* arr, int arrSize)
{
    int* temp = (int*)malloc(sizeof(int) * arrSize);
    MergeSort4(arr, temp, 0, arrSize - 1);
    free(temp);
}


int* generateRandomArray(int n,int bound) {
    int*arr=(int*)malloc(sizeof(int)*n);
    srand((unsigned)time(NULL));
    for (int i=0;i<n;i++) {
        arr[i]=rand()%bound;
    }
    return arr;
}

int main(){
    int n = 100000;

    int* arr1 = generateRandomArray(n, 100000);
    clock_t start1 = clock();
    sort(arr1, n);
    clock_t end1 = clock();

    int* arr2 = generateRandomArray(n, 100000);
    clock_t start2 = clock();
    sort2(arr2, n);
    clock_t end2 = clock();

    int* arr3 = generateRandomArray(n, 100000);
    clock_t start3 = clock();
    sort3(arr3, n);
    clock_t end3 = clock();

    int* arr4 = generateRandomArray(n, 100000);
    clock_t start4 = clock();
    sort4(arr4, n);
    clock_t end4 = clock();

    double timeCost  = (double)(end1 - start1)/CLOCKS_PER_SEC;
    double timeCost2 = (double)(end2 - start2)/CLOCKS_PER_SEC;
    double timeCost3 = (double)(end3 - start3)/CLOCKS_PER_SEC;
    double timeCost4 = (double)(end4 - start4)/CLOCKS_PER_SEC;

    printf("MergeSort,  n=%d: %.6f s\n", n, timeCost);
    printf("MergeSort2, n=%d: %.6f s\n", n, timeCost2);
    printf("MergeSort3, n=%d: %.6f s\n", n, timeCost3);
    printf("MergeSort4, n=%d: %.6f s\n", n, timeCost4);

    free(arr1);
    free(arr2);
    free(arr3);

}
