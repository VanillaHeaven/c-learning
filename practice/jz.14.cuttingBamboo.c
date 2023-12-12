#include<stdio.h>
#include<stdlib.h>

int max(int a, int b, int c) {
    int tmp =  a > b ? a : b;
    return tmp > c ? tmp : c;
}


// 感觉又是一道类似动态规划
int cuttingBamboo(int bamboo_len) {
    if (bamboo_len <= 1) return bamboo_len;

    int n = 0, step = 0;
    // maxnul[n], 表示数字n拆开后的最大乘积
    // maxmul(n) = max{ step * (n - step), step * maxmul(n) }
    // step是从2递增至n-1的步长
    // step * (n - step) 容易忘记,
    // 在查表时, maxmul[n - step]表示数字n - step拆开后的最大乘积。本质上是拆开三个及以上数字的最大乘积。
    // 但不拆也是一种可能。本质是拆开两个数字的最大乘积。
    int *maxmul = (int *) calloc(bamboo_len + 1, sizeof(int));

    maxmul[1] = maxmul[2] = 1;
    for (n = 3; n <= bamboo_len; n++) {
        for (step = 2; step < n; step++) {
            maxmul[n] = max(maxmul[n], (n - step) * step, maxmul[n - step] * step);
        }

        for (step = 1; step <= n; step++) {
            printf("%3d", maxmul[step]);
        }
        printf("\n");
    }

    return maxmul[bamboo_len];
}

int main() {
    int bamboo_len = 12;
    printf("%d\n", cuttingBamboo(bamboo_len));
    return 0;
}