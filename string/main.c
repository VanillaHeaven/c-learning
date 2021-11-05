#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"


void main(int argc, void *argv)
{
    char *s      = "hello";
    char *s_same = "hello";
    char *s_diff = "helloo";
    char *s_copy;
    char *s_cat;
    char *s_sub;
    int   len;

    len = my_strlen(s);

    s_copy = (char *) malloc(len - 1);
    if (s_copy == NULL) return;
    s_copy = my_strcpy(s_copy, s);
    printf("s: %s, len: %d\n", s_copy, len);

    printf("compare s1: %s "
           "and s2: %s, "
           "result code: %d\n", s, s_same, my_strcmp(s, s_same));
    printf("compare s1: %s "
           "and s2: %s, "
           "result code: %d\n", s, s_diff, my_strcmp(s, s_diff));

    s_cat = my_strcat(s, s_diff);
    printf("%s\n", s_cat);

    s_sub = my_strsub(s, 2, 3);
    printf("%s\n", s_sub);

    free(s_copy);
    free(s_cat);
    free(s_sub);
}
