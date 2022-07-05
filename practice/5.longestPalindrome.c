#include <stdio.h>
#include <stdlib.h>


char *longestPalindrome(char *);


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
        printf("%s\n", test_cases[i].e);
        printf("%s\n", longestPalindrome(test_cases[i].e));
    }

    return;
}


char *
longestPalindrome(char *s) {
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