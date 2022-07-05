#include<stdio.h>
#include "user.h"


int main(int argc, void *argv)
{
    char *n = "lili";
    char *p = "1234";
    user_t *user;
    printf("%d\n", login(n, p, user));
    return 0;
}
