#include <stdio.h>

int searchR(int*arr,int l,int r,int target) {

    if (l>r)return -1;

    int mid=l+(r-l)/2;
    if (arr[mid]==target)return mid;
    if (arr[mid]<target) {
        return searchR(arr,mid+1,r,target);
    }
        return searchR(arr,l,mid-1,target);

}

int BinarySearchR(int*arr,int arrSize,int target) {
    return searchR(arr,0,arrSize-1,target);
}

//非递归二分查找法
int search(int*data,int dataSize,int target) {
    int l=0,r=dataSize-1;
    //在data[l,r]的范围中寻找target
    while (l<=r) {
        int mid=l+(r-l)/2;
        if (data[mid]==target) {
            return mid;
        }
        if (data[mid]<target) {
            l=mid+1;
        }
        else {//不会直接return 要写else
            r=mid-1;
        }
    }
    return -1;
}

//------二分查找法的变种-------
//upper：>target的最小值
int upper(int*arr,int arrSize,int target) {
    int l=0,r=arrSize;
    //在arr[l,r]中寻找解
    while (l<r) {
        int mid=l+(r-l)/2;
        if (arr[mid]<=target) {
            l=mid+1;
        }else {
            r=mid;
        }
    }
    return l;
}

//upper_ceil：如果数组中存在元素，返回最大索引；如果不存在元素，返回大于target的最小索引---浮点数ceil运算
int upper_ceil(int*arr,int arrSize,int target) {
    int u=upper(arr,arrSize,target);
    if (u-1>=0&&arr[u-1]==target)return u-1;
        return u;
}

//lower_ceil:>=target的最小索引
int lower_ceil(int*arr,int arrSize,int target) {
    int l=0,r=arrSize;
    while (l<r) {
        int mid=l+(r-l)/2;
        if (arr[mid]<target) {
            l=mid+1;
        }
        else {
            r=mid;
        }
    }
    return l;
}

//lower:<target的最大值
int lower(int*arr,int arrSize,int target) {
    int l=-1,r=arrSize-1;
    //在arr[l,r]找解
    while (l<r) {
        int mid=l+(r-l+1)/2;//避免死循环
        if(arr[mid]>=target) {
            r=mid-1;
        }
        else
            l=mid;
    }
    return l;
}
int main(void)
{
    int arr[] = {1,3,3,3,5,7,9};
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("数组：");
    for(int i=0;i<n;i++){
        printf("%d ", arr[i]);
    }
    printf("\n索引：");
    for(int i=0;i<n;i++){
        printf("%d ", i);
    }
    printf("\n\n");

    // 直接写5组测试，简单直白
    int t;
    t = 3;
    printf("===== target = %d =====\n",t);
    printf("BinarySearchR(递归普通二分): %d\n", BinarySearchR(arr,n,t));
    printf("search(迭代普通二分):      %d\n", search(arr,n,t));
    printf("upper(>target第一个):      %d\n", upper(arr,n,t));
    printf("upper_ceil:                %d\n", upper_ceil(arr,n,t));
    printf("lower_ceil(>=target第一个):%d\n", lower_ceil(arr,n,t));
    printf("lower(<target最大):        %d\n\n", lower(arr,n,t));

    t = 4;
    printf("===== target = %d =====\n",t);
    printf("BinarySearchR(递归普通二分): %d\n", BinarySearchR(arr,n,t));
    printf("search(迭代普通二分):      %d\n", search(arr,n,t));
    printf("upper(>target第一个):      %d\n", upper(arr,n,t));
    printf("upper_ceil:                %d\n", upper_ceil(arr,n,t));
    printf("lower_ceil(>=target第一个):%d\n", lower_ceil(arr,n,t));
    printf("lower(<target最大):        %d\n\n", lower(arr,n,t));

    t = 9;
    printf("===== target = %d =====\n",t);
    printf("BinarySearchR(递归普通二分): %d\n", BinarySearchR(arr,n,t));
    printf("search(迭代普通二分):      %d\n", search(arr,n,t));
    printf("upper(>target第一个):      %d\n", upper(arr,n,t));
    printf("upper_ceil:                %d\n", upper_ceil(arr,n,t));
    printf("lower_ceil(>=target第一个):%d\n", lower_ceil(arr,n,t));
    printf("lower(<target最大):        %d\n\n", lower(arr,n,t));

    t = 0;
    printf("===== target = %d =====\n",t);
    printf("BinarySearchR(递归普通二分): %d\n", BinarySearchR(arr,n,t));
    printf("search(迭代普通二分):      %d\n", search(arr,n,t));
    printf("upper(>target第一个):      %d\n", upper(arr,n,t));
    printf("upper_ceil:                %d\n", upper_ceil(arr,n,t));
    printf("lower_ceil(>=target第一个):%d\n", lower_ceil(arr,n,t));
    printf("lower(<target最大):        %d\n\n", lower(arr,n,t));

    t = 10;
    printf("===== target = %d =====\n",t);
    printf("BinarySearchR(递归普通二分): %d\n", BinarySearchR(arr,n,t));
    printf("search(迭代普通二分):      %d\n", search(arr,n,t));
    printf("upper(>target第一个):      %d\n", upper(arr,n,t));
    printf("upper_ceil:                %d\n", upper_ceil(arr,n,t));
    printf("lower_ceil(>=target第一个):%d\n", lower_ceil(arr,n,t));
    printf("lower(<target最大):        %d\n", lower(arr,n,t));

    return 0;
}