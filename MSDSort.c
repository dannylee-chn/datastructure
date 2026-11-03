#include <stdio.h>
#include <string.h>

//递归算法,根据r位置字符，处理arr[left,right] 闭区间
void sort(char *arr[], int left, int right, int r) {
    if (left >= right) return;

    const int R = 256;
    int cnt[R + 1] = {0};

    for (int i = left; i <= right; i++) {
        int c = (r >= strlen(arr[i])) ? 0 : ((unsigned char)arr[i][r] + 1);
        cnt[c]++;
    }

    int index[R + 2];
    index[0] = 0;
    for (int c = 0; c < R + 1; c++) {
        index[c + 1] = index[c] + cnt[c];
    }

    char *temp[right - left + 1];
    for (int i = left; i <= right; i++) {
        int p = (r >= strlen(arr[i])) ? 0 : ((unsigned char)arr[i][r] + 1);
        temp[index[p]] = arr[i];
        index[p]++;
    }

    for (int i = left; i <= right; i++) {
        arr[i] = temp[i - left];
    }
    
    for (int i = 0; i < R; i++) {
        sort(arr, left + index[i], left + index[i + 1] - 1, r + 1);
    }
}

void MSDSort(char *arr[], int arrSize) {
    sort(arr, 0, arrSize - 1, 0);
}

// ========== 测试用例 ==========
int main(void) {

    char *names[] = {
        "Waka",
        "July",
        "Jack",
        "Mesi",
        "Luka",
        "Henry",
        "Jessie",
        "Wangka",
        "Messie",
        "Lukale"
    };
    int n = sizeof(names) / sizeof(names[0]);

    printf("排序前：\n");
    for(int i = 0; i < n; i++){
        printf("%s ", names[i]);
    }
    putchar('\n');

    MSDSort(names, n);

    printf("排序后：\n");
    for(int i = 0; i < n; i++){
        printf("%s ", names[i]);
    }
    putchar('\n');
    return 0;
}
