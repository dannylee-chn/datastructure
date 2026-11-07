#include <stdbool.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>

#define MOD (1000000007)


//在s中寻找t，找到返回第一个匹配的索引i，找不到返回-1
static inline int bruteforce(char* s,char* t){
    if (strlen(s)<strlen(t))return -1;
    
    //匹配s[i,i+t.length-1]==t?
    for (int i=0;i+strlen(t)-1<strlen(s);i++) {
        int j=0;
        for (;j<strlen(t);j++) {
            if (*(s+i+j)!=*(t+j))
                break;
        }
        if (j==strlen(t))return i;
    }
    return -1;
}

// 防止哈希冲突
bool equals(char*s,int l1,int r1,int l2,int r2) {
    for (int i=l1,j=l2;i<=r1&&j<=r2;i++,j++) {
        if (s[i]!=s[j])
            return false;
    }
    return true;
}

bool equals2(char*s,int l1,int r1,char*t) {
    for (int i=l1,j=0;i<=r1,j<strlen(t);i++,j++) {
        if (s[i]!=t[j])return false;
    }
    return true;
}

static inline int solve(char* s, int left, int right, long* pow26) {
    if (left > right) return 0;
    long prehash = 0, posthash = 0;
    for (int i = left, j = right; i < j; i++, j--) {
        prehash = (prehash * 26LL + (s[i] - 'a')) % MOD;
        posthash = ( (long)(s[j] - 'a') * pow26[right - j] + posthash ) % MOD;

        if(prehash == posthash && equals(s, left, i, j, right)){
            return 2 + solve(s, i + 1, j - 1, pow26);
        }
    }
    return 1;
}

int longestDecomposition(char* text) {
    int n = strlen(text);
    long* pow26 = (long*)malloc(sizeof(long) * n);
    pow26[0] = 1;
    for(int i = 1; i < n; i++){
        pow26[i] = (pow26[i-1] * 26LL) % MOD;
    }

    int ans = solve(text, 0, n - 1, pow26);
    free(pow26);
    return ans;
}

int RabinKarp(char*s,char*t) {

    if (strlen(s)<strlen(t))return -1;
    if (strlen(t)==0)return 0;

    long thash=0,B=256;
    //先求出t的哈希值
    for (int i=0;i<strlen(t);i++) {
        thash=(thash*B+(unsigned char)t[i])%MOD;
    }
    //在s中寻找t
    long powBase=1;
    for (int i=0;i<strlen(t)-1;i++) {
        powBase=powBase*B%MOD;
    }

    long hash = 0;

    int i;
    for (i = 0; i <strlen(t); i++) {
        hash = (hash * B +(unsigned char)s[i])%MOD;
    }
    if (hash==thash&&equals2(s,0,strlen(t)-1,t)) {
        return 0;
    }
    for (i =strlen(t); i < strlen(s); i++) {
        hash = (hash - (unsigned char)s[i - strlen(t)] * powBase % MOD + MOD) % MOD;

        hash = (hash * B + (unsigned char)s[i])%MOD;

        if (hash==thash&&equals2(s,i - strlen(t)+1,i,t)) {
            return i - strlen(t)+1;
        }
    }

    return -1;
}

//KMP
static int* getLPS(char* t) {
    int*lps=(int*)malloc(sizeof(int)*(strlen(t)));
    lps[0] = 0;
    for (int i=1;i<strlen(t);i++) {
        //lps[i]
        int a=lps[i-1];
        while (a>0&&t[i]!=t[a])
            a=lps[a-1];
        if (t[i]==t[a])a++;
        lps[i]=a;
    }
    return lps;
}

static int kmp(char*s,char*t) {
    int n = strlen(s);
    int m = strlen(t);
    if (n < m) return -1;
    if (m == 0) return 0;

    int* lps = getLPS(t);
    int i = 0, j = 0;
    while (i < n) {
        if (s[i] == t[j]) {
            i++;
            j++;
            if (j == m) {
                free(lps);
                return i - m;
            }
        } else if (j > 0) {
            j = lps[j - 1];
        } else {
            i++;
        }
    }
    free(lps);
    return -1;
}

    int main()
    {
        clock_t start, end;
        double cost;

        const int TEXT_LEN = 10000000;
        char *s = (char*)malloc(TEXT_LEN + 1);
        // 生成随机a-z
        for(int i = 0; i < TEXT_LEN; i++)
        {
            s[i] = 'a' + rand() % 26;
        }

        char t[] = "abacabac";
        int pos = 50000;
        int m = strlen(t);
        for(int i = 0; i < m; i++)
        {
            s[pos + i] = t[i];
        }
        s[TEXT_LEN] = '\0';

        printf("==== 超长串测试 ====\n");
        printf("文本长度：%d，模式串：%s，预期位置：%d\n", TEXT_LEN, t, pos);

        start = clock();
        int rk_res = RabinKarp(s, t);
        end = clock();
        cost = (double)(end - start) / CLOCKS_PER_SEC;
        printf("RabinKarp 结果：%d，耗时：%.6f s\n", rk_res, cost);

        start = clock();
        int bf_res = bruteforce(s, t);
        end = clock();
        cost = (double)(end - start) / CLOCKS_PER_SEC;
        printf("bruteforce结果：%d，耗时：%.6f s\n", bf_res, cost);

        // ========== KMP测试 ==========
        start = clock();
        int kmp_res = kmp(s, t);
        end = clock();
        cost = (double)(end - start) / CLOCKS_PER_SEC;
        printf("KMP       结果：%d，耗时：%.6f s\n", kmp_res, cost);

        free(s);
        return 0;
    }
