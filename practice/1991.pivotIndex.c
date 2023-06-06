#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pivotIndex(int* nums, int numsSize){
    int leftSum = 0;
    int rightSum = 0;
    int i = numsSize - 1;

    for (; i >= 0 ; i--) {
        rightSum += nums[i];
    }

    i = 0;
    for (; i < numsSize ; i++) {
        rightSum -= nums[i];

        if (rightSum == leftSum) {
            return i;
        }
        
        leftSum += nums[i];
    }

    // unexist
    return -1;
}

int main()
{
    int nums[2] = {0, 0};
    int numsSize = 2;
    printf("%d\n", pivotIndex(nums, numsSize));

    getchar();

    return 0;
}
