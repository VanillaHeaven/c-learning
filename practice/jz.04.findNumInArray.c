/**
 * @file jz.04.findNumInArray.c
 * @author your name (you@domain.com)
 * @brief 在一个 n * m 的二维数组中，
 *        每一行都按照从左到右递增的顺序排序，
 *        每一列都按照从上到下递增的顺序排序。
 *        请完成一个函数，输入这样的一个二维数组和一个整数，
 *        判断数组中是否含有该整数。
 * @version 0.1
 * @date 2023-10-19
 * @copyright Copyright (c) 2023
 */

#include <stdio.h>
#include <stdlib.h>

int findNumInArray(int **nums, int n, int m, int num) {
    int i = 0, j = m - 1;
    // 先沿边缘下降到山谷
    while (j > -1 && nums[i][j]) j--;
    while (i < m && nums[i][j] < num) i++;

    // 沿着山谷蜿蜒行走, 找出最接近的值;
    while(j >= 0 && i < m) {
        if (nums[i][j] > num) j--;
        else if (nums[i][j] < num) i++;
        else return nums[i][j];
    }

    return -1;
}

int main() {
    int nums[5][5] = {
        {1,   4,  7, 11, 15},
        {2,   5,  8, 12, 19},
        {3,   6,  9, 16, 22},
        {10, 13, 14, 17, 24},
        {18, 21, 23, 26, 30}
    };

    int rows = 5;
    int cols = 5;
    int i = 0;

    int target = 31;

    int **matrixPtr = (int **)malloc(rows * sizeof(int *));
    for (i = 0; i < rows; i++) {
        matrixPtr[i] = nums[i];
    }

    printf("%d\n", findNumInArray(matrixPtr, rows, cols, target));
    return 0;
}