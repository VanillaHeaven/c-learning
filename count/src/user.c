#include "user.h"
#include <my_string.h>

#define MAX_USER 5

user_t users[MAX_USER] = {
    {"lili", "1234"},
    {"lala", "1234"},
    {"lulu", "1234"},
    {"lolo", "1234"},
    {"lele", "1234"}
};


int login(char *n, char *p, user_t *u)
{
//    if (n == NULL || p == NULL || u == NULL) {
//         return -1;
//    }
    char *name = "lili";
    int res = my_strcmp(n, name);

    if (res == 0) return 1;

    return 0;
}
