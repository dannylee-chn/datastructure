#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    SUM,
    MAX
}op;

typedef struct {
    int N;//元素总个数
    int B;//每组元素个数
    int Bn;//组数
    int* data;
    int* blocks;
}SQRT_ARRAY;

void sqrt_create(SQRT_ARRAY*array,int arr[],int arrSize,int op) {
    array->N = arrSize;
    array->data = (int*)malloc(sizeof(int) * array->N);
    for(int i = 0; i < array->N; i++){
        array->data[i] = arr[i];
    }
    array->B = (int)sqrt(arrSize);
    array->Bn = array->N / array->B;
    if(array->N % array->B != 0) {
        array->Bn += 1;
    }
    array->blocks = (int*)malloc(sizeof(int) * array->Bn);
    switch (op) {
        case SUM: {
            for (int i=0;i<arrSize;i++) {
                array->blocks[i/array->B]+=arr[i];
            }
            break;
        }
        case MAX: {
            for(int i = 0; i < arrSize; i++) {
                int b = i / array->B;
                if(i % array->B == 0) {
                    array->blocks[b] = array->data[i];
                } else {
                    if(array->data[i] > array->blocks[b]) {
                        array->blocks[b] = array->data[i];
                    }
                }
            }
            break;
        }
        default:
            // 兜底，防止警告
            break;
    }
}

int sumRange(SQRT_ARRAY* array,int x,int y) {
    if (x<0||x>=array->N||y<0||y>=array->N||x>y)return 0;

    int bstart=x/array->B;
    int bend=y/array->B;

    int res=0;
    if (bstart==bend) {
        for (int i=x;i<=y;i++) {
            res+=array->data[i];
        }
        return res;
    }
    for (int i=x;i<(bstart+1)*array->B;i++) {
        res+=array->data[i];
    }
    for (int b=bstart+1; b<bend;b++) {
        res+=array->blocks[b];
    }
    for (int i=bend*array->B;i<=y;i++) {
        res+=array->data[i];
    }
    return res;
}

//动态维护
void update_sum(SQRT_ARRAY* array,int i,int val) {
    if (i<0||i>=array->N)return;
    int b=i/array->B;
    array->blocks[b]-=array->data[i];
    array->blocks[b]+=val;
    array->data[i]=val;
}

void sqrt_destroy(SQRT_ARRAY* array) {
    free(array->data);
    free(array->blocks);
}

int main() {
    int nums[] = {-2, 0, 3, -5, 2, -1};
    int n = sizeof(nums)/sizeof(nums[0]);

    SQRT_ARRAY sa;
    sqrt_create(&sa, nums, n, SUM);
    printf("块大小 B = %d，块数量 Bn = %d\n", sa.B, sa.Bn);

    printf("sum(0,2) = %d  预期：1\n", sumRange(&sa,0,2));
    printf("sum(2,5) = %d  预期：-1\n", sumRange(&sa,2,5));
    printf("sum(0,5) = %d  预期：-3\n", sumRange(&sa,0,5));

    // 更新：下标3，原值 -5 → 改成10
    update_sum(&sa, 3, 10);
    printf("\n更新 index=3 为10之后：\n");
    printf("sum(0,5) = %d  预期：12\n", sumRange(&sa,0,5));

    sqrt_destroy(&sa);
    return 0;
}