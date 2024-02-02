#include <stdio.h>
#include <stdlib.h>


int *binary(int n, int *size) {
    int  nn = n;
    int  i  = 1;
    int *bi = NULL;

    while(nn != 0) {
        (*size)++;
        nn /= 2;
    }

    bi = (int *) calloc( (*size + 1), sizeof(int));

    nn = n;    
    while(nn != 0) {
        bi[i++] = nn % 2;
        nn /= 2;
    }

    return bi;
}


// x: 底数
// n: 指数
// 思路: 
//  n可能是一个大整数, 如果使用暴力法, 使用循环获得x*x*x..., 时间复杂度是O(n)
//  根据乘方的法则, a^n * a^m = a^(n + m)
//  我们可以将n转化为二进制, 然后只要获得对应二进制位的乘方值, 相乘即可获得结果, 时间复杂度log(n)
double myPow(double x, int n) {
    // 边界情况
    if (n == 0 || x == 1) return 1;

    double  ans  = 1;
    int     size = 0;
    int     i    = 0;
    int    *bi   = NULL;
    double *dp   = NULL;

    // 先将指数转化为二进制
    bi = binary(n, &size);

    // dp数组预先存储了底数x在对应二进制数位上的乘方值
    // dp[i] = x^i
    dp = (double *) malloc( (size + 1) * sizeof(double));
    dp[0] = 1;
    dp[1] = x;  
    for (i = 2; i <= size; i++) {
        dp[i] = dp[i - 1] * dp[i - 1];
    }

    // 根据n的二进制, 将对应二进制位上的乘方值相乘, 即可得到目标值
    for (i = 1; i <= size; i++) {
        if (bi[i]) {
            ans *= dp[i];
        }
    }

    // n是负数时, 乘方取倒数
    if (n < 0) {
        return 1 / ans;
    }

    return ans;
}


int main() {
    double x = 2.0000;
    int n = -2;

    printf("%f\n", myPow(x, n));

    return 0;
}
