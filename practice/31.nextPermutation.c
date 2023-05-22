#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void swap(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;
}


void swapNums(int* nums, int start, int end)
{
    if (start > end) return;

    while (start <= end) {
        swap(&nums[start], &nums[end]);
        start++;
        end--;
    }
}


/*
 */
void nextPermutation(int* nums, int numsSize)
{
    int minLeft = numsSize - 2;
    int maxRight = numsSize - 1;

    // 找到最小的右侧值
    for (; minLeft >= 0; minLeft--) {
        if (nums[minLeft] < nums[minLeft + 1]) {
            break;
        }
    }

    if (minLeft < 0) {
        return swapNums(nums, 0, numsSize - 1);
    }

    // 找到最小的大于右侧值的左侧值
    for (; maxRight > minLeft; maxRight--) {
        if (nums[maxRight] > nums[minLeft]) {
            break;
        }
    }
    
    swap(&nums[minLeft], &nums[maxRight]);
    swapNums(nums, minLeft + 1, numsSize - 1);
}


int main()
{
    int numsSize = 3;
    int nums[] = {1,5,1};
    nextPermutation(nums, numsSize);

    int i = 0;
    for (; i < numsSize; i++)
        printf("%d ", nums[i]);

    printf("\n");

    getchar();

    return 0;
}
