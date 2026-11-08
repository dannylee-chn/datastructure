#include <stdlib.h>
#include <time.h>

//洗牌算法
typedef struct {
    int* origin;
    int size;
} Solution;

Solution* solutionCreate(int* nums, int numsSize) {
        Solution*res=(Solution*)malloc(sizeof(Solution));
        res->origin=(int*)malloc(sizeof(int)*(numsSize));
        for (int i=0;i<numsSize;i++) {
            res->origin[i]=nums[i];
        }
        res->size=numsSize;
        return res;
}

int* solutionReset(Solution* obj, int* retSize) {
    *retSize = obj->size;
    return obj->origin;
}

int* solutionShuffle(Solution* obj, int* retSize) {
    *retSize = obj->size;
    int *buf = malloc(sizeof(int) * obj->size);
    for(int i = 0; i < obj->size; i++){
        buf[i] = obj->origin[i];
    }
    for(int i = obj->size - 1; i > 0; i--){
        int r = rand() % (i + 1);
        int tmp = buf[i];
        buf[i] = buf[r];
        buf[r] = tmp;
    }
    return buf;
}

void solutionFree(Solution* obj) {
    free(obj->origin);
    free(obj);
}

//蓄水池算法

struct ListNode {
    int val;
    struct ListNode *next;
};

typedef struct {
    struct ListNode* head;
} Solution2;


Solution2* solutionCreate2(struct ListNode* head) {
    Solution2*res=malloc(sizeof(Solution2));
    res->head=head;
    return res;
}

int solutionGetRandom(Solution2* obj) {
    int res=obj->head->val;
    int index=1;
    for (struct ListNode*cur=obj->head->next;cur!=NULL;cur=cur->next,index++) {
        int j=rand()%(index+1);
        if (j==0)res=cur->val;
    }
    return res;
}

void solutionFree2(Solution2* obj) {
    free(obj);
}

