#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int get_middle(int a, int b, int c)
{
    if (a > b) {
        if (c > a) return a;
        if (b > c) return b;

    } else { // a < b
        if (c > b) return b;
        if (a > c) return a;
    }

    return c;
}

void swap(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;
}


void quicksort(int nums[], int left, int right)
{
    if (right <= left) return;

    if (right == left + 1) {
        if (nums[left] > nums[right]) {
            swap(&nums[left], &nums[right]);
        }
        return;
    }

    int index = 0;
    int middle = get_middle(nums[left], nums[(left + right) / 2], nums[right]);
    index = nums[left] == middle ? left : nums[right] == middle ? right : (left + right) / 2;
    swap(&nums[left], &nums[index]);
    index = left;

    int i = left, j = right;

    while (i < j) {
        while (j > i && nums[j] >= nums[index]) j--;
        swap(&nums[index], &nums[j]);
        index = j;

        while(i < j && nums[i] < nums[index]) i++;
        swap(&nums[index], &nums[i]);
        index = i;
    }

    nums[index] = middle;

    quicksort(nums, left, index - 1);
    quicksort(nums, index + 1, right);
}


int binarySearch(int *nums, int iLeft, int iRight, int iTarget) {
    if (iRight < iLeft) return -1;

    if (iLeft == iRight) {
        if (iTarget == nums[iLeft]) {
            return iLeft;
        } else {
            return -1;
        }
    }

    int iMiddle = (iLeft + iRight) / 2;

    if (nums[iMiddle] > iTarget) {
        return binarySearch(nums, iLeft, iMiddle - 1, iTarget);
    } else if (nums[iMiddle] < iTarget) {
        return binarySearch(nums, iMiddle + 1, iRight, iTarget);
    } else {
        return iMiddle;
    }
}


/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** threeSum(int* nums, int numsSize, int *returnSize, int **returnColumnSizes){
    int   iIndex1     = 0;
    int   iIndex2     = 1;
    int   iRightLimit = numsSize - 1;
    int   iArraysSize = 1;
    int **pArrays     = (int **) malloc(sizeof(int *) * iArraysSize);

    *returnColumnSizes = (int *) malloc(sizeof(int) * iArraysSize);
    *returnSize        = 0;

    // if (numsSize <= 3) do something special

    quicksort(nums, 0, numsSize - 1);

    while (iIndex1 < numsSize && nums[iIndex1] <= 0) {
        if (iIndex1 > 0 && nums[iIndex1] == nums[iIndex1 - 1]) {
            iIndex1++;
            continue;
        }
        iIndex2 = iIndex1 + 1;
        iRightLimit = numsSize;
        while (iIndex2 < iRightLimit) {
            if (iIndex2 - 1 > iIndex1 && nums[iIndex2] == nums[iIndex2 - 1]) {
                iIndex2++;
                continue;
            }
            int iTarget = -1 * (nums[iIndex1] + nums[iIndex2]);
            int iIndex3 = binarySearch(nums, iIndex2 + 1, iRightLimit - 1, iTarget);
            if (iIndex3 >= 0 && iIndex3 > iIndex2) {
                pArrays[*returnSize] = (int *) malloc(sizeof(int) * 3);
                pArrays[*returnSize][0] = nums[iIndex1];
                pArrays[*returnSize][1] = nums[iIndex2];
                pArrays[*returnSize][2] = nums[iIndex3];

                (*returnColumnSizes)[*returnSize] = 3;

                (*returnSize)++;

                if (*returnSize == iArraysSize) {
                    iArraysSize *= 2;
                    pArrays = (int **) realloc(pArrays, iArraysSize * sizeof(int *));
                    *returnColumnSizes = (int *)
                        realloc(*returnColumnSizes, iArraysSize * sizeof(int));
                }

                iRightLimit = iIndex3;
            }
            iIndex2++;
        }
        iIndex1++;
    }

    return pArrays;
}


int main()
{
    int   iIndex1 = 0;
    int   iIndex2 = 0;
    int **pArrays = NULL;
    int   nums[6] = {0, 0, 0, 0};

    int   pReturnSize = 0;
    int   iReturnnColumnSize = 0;
    int **pReturnnColumnSize = (int **) malloc(sizeof(int *));

    pArrays = threeSum(nums, 4, &pReturnSize, pReturnnColumnSize);

    for (; iIndex1 < pReturnSize; iIndex1++) {
        for (iIndex2 = 0; iIndex2 < (*pReturnnColumnSize)[iIndex1]; iIndex2++) {
            printf("%d ", pArrays[iIndex1][iIndex2]);
        }
        printf("\n");
        free(pArrays[iIndex1]);
    }

    free(pArrays);
    free(*pReturnnColumnSize);
    free(pReturnnColumnSize);

    printf("\n");
    return 0;
}
