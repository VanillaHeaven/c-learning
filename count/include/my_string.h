#ifndef MYSTRING_H
#define MYSTRING_H

int my_strlen(char *s);
int my_strcmp(char *s1, char *s2);
char *my_strcpy(char *dest, char *src);
char *my_strcat(char *s1, char *s2);
char *my_strsub(char *s, int start, int len);

#endif

#ifndef NULL
#define NULL 0
#endif
