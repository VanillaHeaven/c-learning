#include <stdio.h>


typedef struct
{
    char *answer;
    char *example;
} test_case_t;



void main(int argc, void **argv) {

    test_case_t test_cases[] = {
        {"aaaa", "aaaa"},
        {"abba", "abba"},
        {"aaaaaaaabbbaaaaaaaaabbbaaaaaaaa", "aaaaaaaabbbaaaaaaaaabbbaaaaaaaa"},
        {"encleefefff", "efe"},
        {NULL, NULL}
    };

    int i = 0;

    for(; test_cases[i].example != NULL; i++) {
        printf("%s\n", test_cases[i].example);
        printf("%s\n", test_cases[i].answer);
    }

    return;
}