#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

void main(int argc, void* argv[]) {
    char c;
    int child;
    int pid    = fork();

    if (pid == 0) {
        printf("My parent is %d.\n", getppid());
        while((c = getchar()) != '\n') {
            printf("%c", c);
        }
        printf("\n");
    }
    else {
        child = waitpid(-1, NULL, 0);
        printf("My child %d is exit.\n", child);
    }

    return;
}
