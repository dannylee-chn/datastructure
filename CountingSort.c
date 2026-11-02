#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct {
    char* name;
    int score;
}Student;

static inline void my_printf(Student* student) {
    printf("name: %s, score: %d\n", student->name, student->score);
}

int main(void) {
    int n = 26 * 26 * 26 * 26;
    printf("总数量：%d\n", n);
    Student* students = (Student*)malloc(sizeof(Student) * n);
    if (students == NULL) {
        perror("malloc fail");
        return 1;
    }

    int k = 0;
    char buf[5];
    srand((unsigned)time(NULL));
    for (char c1 = 'a'; c1 <= 'z'; c1++) {
        for (char c2 = 'a'; c2 <= 'z'; c2++) {
            for (char c3 = 'a'; c3 <= 'z'; c3++) {
                for (char c4 = 'a'; c4 <= 'z'; c4++) {
                    buf[0] = c1;
                    buf[1] = c2;
                    buf[2] = c3;
                    buf[3] = c4;
                    buf[4] = '\0';
                    students[k].name = strdup(buf);
                    students[k].score = rand() % 101;
                    k++;
                }
            }
        }
    }

    // ========== 稳定计数排序 ==========
    int R = 101;
    int cnt[R];
    for(int i = 0; i < R; i++) cnt[i] = 0;

    //O(n)
    for (int i = 0; i < n; i++) {
        cnt[students[i].score]++;
    }

    //O(R)
    int index[R + 1];
    for(int i = 0; i <= R; i++) index[i] = 0;
    for (int i = 0; i < R; i++) {
        index[i+1] = index[i] + cnt[i];
    }

    //O(n)
    Student* temp = (Student*)malloc(sizeof(Student) * n);
    for (int i = 0; i < n; i++) {
        temp[index[students[i].score]] = students[i];
        index[students[i].score]++;
    }
    // 拷贝回原数组O(n)
    for (int i = 0; i < n; i++)
        students[i] = temp[i];

    for (int i = 0; i < 20; i++) {
        my_printf(&students[i]);
    }

    // ========= 内存释放 =========
    free(temp);
    for(int i = 0; i < n; i++){
        free(students[i].name);
    }
    free(students);
    return 0;
}
