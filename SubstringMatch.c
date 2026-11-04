
#include <stdbool.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

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



int main() {
    char* s="hello,this is lidanininini";
    char* t="ni";
    printf("%d",bruteforce(s,t));
}