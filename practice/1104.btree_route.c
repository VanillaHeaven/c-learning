#include <stdio.h>
#include <stdlib.h>


#define TEST              1

typedef u_char      u_char;
typedef struct test_case_s test_case_t;

struct test_case_s
{
    int   label;
};


int*    pathInZigZagTree(int label, int* returnSize);
int     my_pow(int x, int n);


void
main(int argc, void **argv) {

    test_case_t test_cases[] = {
        {14},
        {26},
        {0},
    };

    int  i = 0;
    int  j = 0;
    int  size = 0;
    int *path = NULL;

    for(; test_cases[i].label; i++) {
        printf("测试用例: %d\n", test_cases[i].label);
        path = pathInZigZagTree(test_cases[i].label, &size);

        for (; j < size;) {
            printf("%d\n", path[j++]);
        }

        free(path);
        size = 0;
        j = 0;
        printf("===============\n");
    }

    return;
}


int*
pathInZigZagTree(int label, int* returnSize)
{
    int *path = NULL;
    int l     = label;
    int pm    = 0;

    while(l)
    {
        l /= 2;
        (*returnSize)++;
    }

    path = (int *) calloc(*returnSize, sizeof(int));

    l = *returnSize;
    path[--l] = label;
    pm = my_pow(2, l);

    for (;l > 0; l--)
    {
        path[l - 1] = pm - (path[l] - pm + 2) / 2;
        pm /= 2;
    }

    return path;
}


int
my_pow(int x, int n)
{
    int a = 1;
    while(n--) a *= x;
    return a;
}
