#include <stdio.h>
#include <stdlib.h>

// 新建一个长度为N的数组来存储访问过的状态
int findRepeatNum1(int nums[], int size) {
    int i = 0;
    int *sorted = (int *) calloc(size, sizeof(int));

    for (i = 0; i < size; i++) {
        if (sorted[nums[i]] > 0) {
            return nums[i];
        }
        sorted[nums[i]]++;
    }

    return -1;
}

// 直接在原数组上存储访问过的状态
int findRepeatNum2(int nums[], int size) {
    int i = 0;

    // 思路就是将nums数组的下标跟内容对齐, 因为题干说nums数组内数字小于数组大小n, 可以利用这个条件来使用原数组来存储状态信息。
    for (i = 0; i < size; i++) {
        // 如果当前下标与实际内容一致, 说明该位置内容已到位
        // 如果当前下标与实际内容不匹配, 说明该内容放置位置不正确, 尝试将它挪到正确的位置,
        // 如果正确的位置已经有了同样的内容, 说明数字重复了
        if (nums[i] != i) {
            if (nums[nums[i]] != nums[i]) {
                int tmp = nums[i];
                nums[i] = nums[nums[i]];
                nums[tmp] = tmp;
                i--;

            } else {
                return nums[i];
            }
        }
    }

    return -1;
}


int main() {
    int nums[] = {0, 1, 3, 1, 0};
    printf("%d\n", findRepeatNum1(nums, 5));
    printf("%d\n", findRepeatNum2(nums, 5));
    return 0;
}

