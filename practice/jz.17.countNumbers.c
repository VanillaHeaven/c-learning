#include <stdio.h>
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* countNumbers(int cnt, int* returnSize) {
    int  n = 1, i = 1;
    int *countN = NULL;

    // 计算cnt位数的最大值
    while(cnt-- > 0) n *= 10;
    n--;
    *returnSize = n;

    countN = (int *) malloc(n * sizeof(int));
    for (i = 0; i < n; i++) countN[i] = i + 1;

    return countN;
}