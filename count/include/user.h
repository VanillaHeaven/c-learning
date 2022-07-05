#ifndef USER_H
#define USER_H

typedef struct user_s user_t;

struct user_s {
    char *name;
    char *password;
};


int login(char *n, char *p, user_t *u);

#endif


#ifndef NULL
#define NULL 0
#endif
