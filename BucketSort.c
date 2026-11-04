#include <stdio.h>
#include<limits.h>

#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))


//递归函数
void sort(int arr[],int left,int right,int B,int temp[]) {
     if (left>=right)return;
     int maxv=INT_MIN;
     int minv=INT_MAX;
     for (int i=left;i<=right;i++) {
          maxv=MAX(maxv,arr[i]);
          minv=MIN(minv,arr[i]);
     }
     if (maxv==minv)return;

     int cnt[B];
     int index[B+1];
     for(int i=0;i<B;i++) cnt[i]=0;
     for(int i=0;i<=B;i++) index[i]=0;

     int d=(maxv-minv+1)/B+(((maxv-minv)%B)>0?1:0);//整形除法上取整，避免浮点运算精度误差

     for (int i=left;i<=right;i++) {
          cnt[(arr[i]-minv)/d]++;
     }

     for (int i=0;i<B;i++) {
          index[i+1]=index[i]+cnt[i];
     }

     for (int i=left;i<=right;i++) {
          int p=(arr[i]-minv)/d;
          temp[left+index[p]]=arr[i];
          index[p]++;
     }

     for (int i=left;i<=right;i++) {
          arr[i]=temp[i];
     }

     sort(arr,left,left+index[0]-1,B,temp);
     for (int i=0;i<B-1;i++) {
          sort(arr,left+index[i],left+index[i+1]-1,B,temp);
     }

}

void BucketSort(int arr[],int arrSize,int B) {
     if (B<=1)perror("B must be >1");

     int temp[arrSize];
     sort(arr,0,arrSize-1,B,temp);
}

void printArr(int a[],int n){
     for(int i=0;i<n;i++) printf("%d ",a[i]);
     printf("\n");
}

int main(){
     //测试1：普通乱序
     int a1[] = {5,3,8,1,9,2,7,4,6};
     int n1 = sizeof(a1)/sizeof(a1[0]);
     BucketSort(a1,n1,3);
     printArr(a1,n1);

     //测试2：有重复元素
     int a2[] = {2,2,1,5,3,2,5,1};
     int n2 = sizeof(a2)/sizeof(a2[0]);
     BucketSort(a2,n2,4);
     printArr(a2,n2);

     //测试3：逆序
     int a3[] = {10,9,8,7,6,5,4,3,2,1};
     int n3 = sizeof(a3)/sizeof(a3[0]);
     BucketSort(a3,n3,3);
     printArr(a3,n3);

     //测试4：大量相同
     int a4[] = {7,7,7,7,7};
     int n4 = sizeof(a4)/sizeof(a4[0]);
     BucketSort(a4,n4,2);
     printArr(a4,n4);

     return 0;
}

