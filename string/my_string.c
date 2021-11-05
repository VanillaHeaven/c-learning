#include <stdlib.h>
#include <assert.h>
#include "my_string.h"


int my_strlen(char *s)
{
    assert(s != NULL);

    int len = 0;
    while(*s++ != '\0') len++;
    return len;
}


char* my_strcpy(char *dest, char *src)
{
    assert(dest != NULL && src != NULL);

    char *d = dest;

    while(*src != '\0') {
        *dest++ = *src++;
    }
    dest = '\0';

    return d;
}


int my_strcmp(char *s1, char *s2)
{
    assert(s1 != NULL && s2 != NULL);

    while(*s1 != '\0' || *s2 != '\0') {
        if (*s1 != *s2) return *s1 > *s2 ? 1 : -1;
        s1++; s2++;
    }

    return 0;
}


char *my_strcat(char *s1, char *s2)
{
    assert(s1 != NULL && s2 != NULL);

    char *s, *ret;
    int   len;

    len = my_strlen(s1) + my_strlen(s2);
    ret = s = (char *) malloc(len + 1);
    if (ret == NULL) return NULL;
    while(*s1 != '\0') *s++ = *s1++;
    while(*s2 != '\0') *s++ = *s2++;
    s = '\0';

    return ret;
}


char *my_strsub(char *s, int start, int len)
{
    assert(s != NULL);

    char *ret, *str;

    ret = str = (char *) malloc(len + 1);
    if (!ret) return NULL;

    s += start * sizeof(char);
    while(*s != '\0' && len-- != 0) *str++ = *s++;
    str = '\0';

    return ret;
}
