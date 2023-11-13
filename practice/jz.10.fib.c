#include <stdio.h>
#include <stdlib.h>


int fib(int n) {
    if (n < 2) { return n; }

    int i = 0;
    int a[3] = {0, 1, 1};

    for (i = 2; i <= n; i++) {
        a[2] = (a[1] + a[0]) % 1000000007;
        a[0] = a[1];
        a[1] = a[2];
    }

    return a[2];
}

int fib_by_matrix(int n) {
    if (n < 2) return n;

    int i = 1;
    int a = 0, b = 1;
    int mod = 1000000007;
    int res[2] = {1, 0};
    long int db[8][2][2] = {
        {{1, 1}, {1, 0}},
        {{0, 0}, {0, 0}},
        {{0, 0}, {0, 0}},
        {{0, 0}, {0, 0}},
        {{0, 0}, {0, 0}},
        {{0, 0}, {0, 0}},
        {{0, 0}, {0, 0}},
        {{0, 0}, {0, 0}}
    };

    // init matrix
    for (i = 1; i < 8; i++) {
        db[i][0][0] = (db[i - 1][0][0] * db[i - 1][0][0] + db[i - 1][0][1] * db[i - 1][1][0]) % mod;
        db[i][0][1] = (db[i - 1][0][0] * db[i - 1][0][1] + db[i - 1][0][1] * db[i - 1][1][1]) % mod;
        db[i][1][0] = (db[i - 1][1][0] * db[i - 1][0][0] + db[i - 1][1][1] * db[i - 1][1][0]) % mod;
        db[i][1][1] = (db[i - 1][1][0] * db[i - 1][0][1] + db[i - 1][1][1] * db[i - 1][1][1]) % mod;
    }

    for (i = 0, n--; n != 0; n = n / 2, i++) {
        if (n % 2 == 1) {
            a = (db[i][0][0] * res[0] + db[i][0][1] * res[1]) % mod;
            b = (db[i][1][0] * res[0] + db[i][1][1] * res[1]) % mod;
            res[0] = a;
            res[1] = b;
        }
    }

    return res[0];
}

int main() {
    int n = 0;
    scanf("%d", &n);
    printf("res = %d\n", fib(n));
    printf("res = %d\n", fib_by_matrix(n));
}

/**
 * @brief
 *  T * T * T  * f(1) = f(4)
 *               f(0)   f(3)
 */