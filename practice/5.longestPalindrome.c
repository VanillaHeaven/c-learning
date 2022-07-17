#include <stdio.h>
#include <stdlib.h>


char *longestPalindromeByDynamic(char *);
char *longestPalindromeByMalache(char *);


typedef struct
{
    char *e;
    char *a;
} test_case_t;



void
main(int argc, void **argv) {

    test_case_t test_cases[] = {
        {"abba", "abba"},
        {"a", "a"},
        {"aennvvlenffnalef", "nffn"},
        {NULL, NULL}
    };

    int i = 0;

    for(; test_cases[i].e != NULL; i++) {
        printf("测试用例: %s\n", test_cases[i].e);
        printf("动态规划: %s\n", longestPalindromeByDynamic(test_cases[i].e));
        printf("马拉车解: %s\n", longestPalindromeByMalache(test_cases[i].e));
        printf("\n");
    }

    return;
}


char *
longestPalindromeByDynamic(char *s) {
    int    len = -1;
    int    i   = 0;
    int    j   = 0;
    int    l   = 0;
    int    max = 0;
    char  *ns  = NULL;
    char **rt  = NULL;

    while(s[++len] != '\0');

    if (len <= 1)
        return s;

    rt = (char**) malloc(len * sizeof(char *));
    while (i < len)
        rt[i++] = (char *) calloc(len, sizeof(char));

    i = -1;
    while (++i < len) {
        j = -1;
        rt[i][i] = 1;
        while (++j < i)
            if (s[j] == s[i]
                && (i - j < 3
                    || rt[j + 1][i - 1]))
            {
                rt[j][i] = 1;
                if (i - j > max) {
                    max = i - j;
                    l = j;
                }
            }
    }

    i = 0;
    j = l;
    ns = (char *) malloc(max + 2);
    while (j <= l + max)
        ns[i++] = s[j++];
    ns[i] = '\0';
    
    i = 0;
    while (i < len)
        free(rt[i++]);
        
    free(rt);

    return ns;
}


char *
longestPalindromeByMalache(char *s) {
    int        i     = -1;
    int        im    = 0;
    int        len   = 0;
    int        l     = 0; 
    int        r     = 0;
    int        c     = 0;
    int        t     = 0;
    int        max_c = 0;
    char      *ns    = NULL;
    short int *rc    = NULL;

    while (s[++i] != '\0');

    len = 2 * i + 1;
    ns = (char *) malloc(len);
    rc = (short int *) malloc(len * sizeof(short int));

    while(i > 0) {
        ns[2 * i] = '#';
        ns[2 * i - 1] = s[i - 1];
        // init
        rc[2 * i - 1] = rc[2 * i] = 0;

        i--;
    }
    ns[0] = '#';
    rc[0] = 0;

    i = -1;
    while(++i < len) {
        // 校验镜像半径
        im = 2 * c - i;

        if (i <= r) {
            if (im - rc[im] <= l) {
                t = r - i + 1;
            } else {
                rc[i] = rc[im];
                continue;
            }
        } else {
            t = 1;
        }

        while (
            i - t >= 0
            && i + t < len
            && ns[i - t] == ns[i + t]
        ) t++;

        rc[i] = --t;

        if (t > rc[max_c]) {
            max_c = i;
        }

        if (i + t > r) {
            c = i;
            r = i + t;
            l = i - t;
        }
    }

    free(ns);

    i = 0;
    l = (max_c - rc[max_c]) / 2;
    r = (max_c + rc[max_c] - 1) / 2;
    ns = (char *) malloc(r - l + 2);

    while(l <= r) ns[i++] = s[l++];
    ns[i] = '\0';
    
    free(rc);
    
    return ns;
}