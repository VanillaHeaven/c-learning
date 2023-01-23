#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

    int index = left;
    int i = left, j = right;

    while (i < j) {
        while (j > i && nums[j] >= nums[index]) j--;
        swap(&nums[index], &nums[j]);
        index = j;

        while(i < j && nums[i] < nums[index]) i++;
        swap(&nums[index], &nums[i]);
        index = i;
    }

    quicksort(nums, left, index - 1);
    quicksort(nums, index + 1, right);
}


/*
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 * 
 * 这道题解法的几何理解：
 * 假设固定i，以j为列，k值为行，计算j-k的和，形成一张表
 * -----
 *  ----
 *   ---
 *    --
 *     -
 * 表中的值，从左往右递增，从上往下递增。
 * 由于 j<k，所以所有值的结果构成一个三角形。
 * 
 * 计算表中所有值与target的差，并取绝对值，
 * 差值越小，绝对值越小，形成“山谷”；差值大，形成山坡；
 * 整个表，像是一块三角形的披萨，从中被对折。
 * 
 * 求解的过程，
 * 就是沿着披萨的边缘，快速下降到山谷的位置，
 * 然后沿着山谷遍历，找到最小的差值。
 * 
 * 【对折的披萨】images/fold-pizza.jpg
 */
int threeSumClosest(int* nums, int numsSize, int target){
    int i = 0, j = 0, k = 0;

    int closest = nums[0] + nums[1] + nums[2] - target;

    quicksort(nums, 0, numsSize - 1);

    while (i < numsSize - 2) {
        j = i + 1;
        k = numsSize - 1;

        // diff is minimal if not moved
        while (j < k) {
            int temp = nums[i] + nums[j] + nums[k] - target;
            
            if (abs(temp) <= abs(closest)) {
                closest = temp;
            }

            if (temp >= 0) {
                k--;
            } else if (temp < 0) {
                j++;
            } else {
                return temp + target;
            }
        }

        i++;
    }

    return closest + target;
}


int main()
{
    int nums[] = {13,252,-87,-431,-148,387,-290,572,-311,-721,222,673,538,919,483,-128,-518,7,-36,-840,233,-184,-541,522,-162,127,-935,-397,761,903,-217,543,906,-503,-826,-342,599,-726,960,-235,436,-91,-511,-793,-658,-143,-524,-609,-728,-734,273,-19,-10,630,-294,-453,149,-581,-405,984,154,-968,623,-631,384,-825,308,779,-7,617,221,394,151,-282,472,332,-5,-509,611,-116,113,672,-497,-182,307,-592,925,766,-62,237,-8,789,318,-314,-792,-632,-781,375,939,-304,-149,544,-742,663,484,802,616,501,-269,-458,-763,-950,-390,-816,683,-219,381,478,-129,602,-931,128,502,508,-565,-243,-695,-943,-987,-692,346,-13,-225,-740,-441,-112,658,855,-531,542,839,795,-664,404,-844,-164,-709,167,953,-941,-848,211,-75,792,-208,569,-647,-714,-76,-603,-852,-665,-897,-627,123,-177,-35,-519,-241,-711,-74,420,-2,-101,715,708,256,-307,466,-602,-636,990,857,70,590,-4,610,-151,196,-981,385,-689,-617,827,360,-959,-289,620,933,-522,597,-667,-882,524,181,-854,275,-600,453,-942,134};
    printf("%d\n",  threeSumClosest(nums, 211, -2805));

    getchar();

    return 0;
}
