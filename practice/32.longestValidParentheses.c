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


int longestValidParentheses(char * s)
{
    int i = 0, j = 1, max = 0;

    // 获取字符串长度
    while (*(s + i) != '\0') i++;
    if (i < 2) return 0;

    // 申请数组，记录到每个下标时，最长的匹配串长度
    short int* len_record = (short int *) calloc(i, sizeof(short int));

    for ( ; j <= i ; j++) {
        if (s[j] == ')') {
            int match_left = j - 1;

            if (len_record[j - 1] != 0)
                match_left = j - 1 - len_record[j - 1];

            if (match_left < 0) continue;

            if (s[match_left] == '(')
                len_record[j] = len_record[j - 1] + 2;

            if (len_record[j] && match_left > 1 && len_record[match_left - 1] != 0)
                len_record[j] += len_record[match_left - 1];

            if (len_record[j] > max) max = len_record[j];
        }
    }

    free(len_record);

    return max;
}


int main()
{
    //         01000020406080a0ce0 
    // char* s = "()(((()()()()()())()()()()()))";
    char* s = "()()))))()()(";
    printf("%d\n", longestValidParentheses(s));

    getchar();

    return 0;
}
