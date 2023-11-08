#include <stdio.h>
#include <stdlib.h>

char *replaceSpace(char *s) {
    int i = 0;
    int c = 0;
    char *ns = NULL;

    for(i = 0, c = 0; s[i] != '\0'; i++) {
        if (s[i] == ' ') {
            c += 3;
        } else {
            c++;
        }
    }

    ns = (char *) malloc(c * sizeof(char));

    for(i = 0, c = 0; s[i] != '\0'; i++) {
        if (s[i] == ' ') {
            ns[c++] = '%';
            ns[c++] = '2';
            ns[c++] = '0';
        } else {
            ns[c++] = s[i];
        }
    }

    return ns;
}

int main() {
    char *s = "hello world !";
    char *ns = replaceSpace(s);
    printf("%s\n", ns);
    free(ns);
    return 0;
}