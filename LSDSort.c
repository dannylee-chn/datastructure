#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void LSDSort(int n, int W, char arr[n][W+1]) {
    for (int i = 0; i < n; i++) {
        if (strlen(arr[i]) != W) {
            printf("Error: All Strings' length must be same.\n");
            exit(EXIT_FAILURE);
        }
    }

    for (int r = W - 1; r >= 0; r--) {
        const int R = 256;
        int cnt[256] = {0};

        for (int i = 0; i < n; i++) {
            cnt[(unsigned char)arr[i][r]]++;
        }

        int index[R + 1];
        index[0] = 0;
        for (int c = 0; c < R; c++) {
            index[c + 1] = index[c] + cnt[c];
        }

        char temp[n][W + 1];
        for (int i = 0; i < n; i++) {
            int c = (unsigned char)arr[i][r];
            strcpy(temp[index[c]], arr[i]);
            index[c]++;
        }

        for (int i = 0; i < n; i++) {
            strcpy(arr[i], temp[i]);
        }
    }
}

int main(void) {
    char strs[5][5] = {
        "Waka",
        "July",
        "Jack",
        "Mesi",
        "Luka"
    };
    int n = 5;
    int len = 4;

    printf("排序前：\n");
    for (int i = 0; i < n; i++) {
        printf("%s ", strs[i]);
    }
    putchar('\n');

    LSDSort(n, len, strs);

    printf("排序后：\n");
    for (int i = 0; i < n; i++) {
        printf("%s ", strs[i]);
    }
    putchar('\n');
    return 0;
}
