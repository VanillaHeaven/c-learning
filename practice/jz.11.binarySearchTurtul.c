#include <stdio.h>
#include <stdlib.h>

// 题目描述不清啊,
// 题目意思是有一个递增的数组,
// 然后从中间截断, 将截断的前半部分, 平移到数组尾部, 
// 然后求解这个数组最小值

int stock_management(int* stock, int stocksize) {
    int min = stock[0];
    int left = 0;
    int right = stocksize - 1;
    int mid = (right - left) / 2 + left;

    while (left < right) {
        if (stock[mid] > stock[right]) {
            left = mid + 1;
        } else if (stock[mid] < stock[right]) {
            right = mid;
        } else {
            right--;
        }
        mid = (right - left) / 2 + left;
    } 

    return stock[left];
}

int main() {
    int len = 5;
    int a[10] = {4,5,8,3,4};

    printf("%d\n", stock_management(a, len));

    return 0;
}