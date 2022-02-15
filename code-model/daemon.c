#include "process.h"


int my_daemon();


int main(int argc, char *const *argv) {

    if (my_daemon() == PRO_OK) {
        printf("====== success\n");

    } else {
        printf("====== error\n");
    };

    return 0;
}


int my_daemon() {

    int pid, fd;

    switch(pid = fork()) {

    case -1:
        printf("====== error");
        break;

    case 0:
        printf("====== child process, %d\n", getpid());
        break;

    default:
        printf("====== parent process, %d\n", getpid());
        exit(0);
    }

    if(setsid() == -1) {
        return PRO_ERR;
    }

    umask(0);

    sleep(10);
    
    printf("====== child process end\n");

    fd = open("/dev/null", O_RDWR);
    if(fd == -1) {
        return PRO_ERR;
    }

    if(dup2(fd, STDIN_FILENO) == -1) {
        return PRO_ERR;
    }

    if(dup2(fd, STDOUT_FILENO) == -1) {
        return PRO_ERR;
    }

    if(close(fd) == -1) {
        return PRO_ERR;
    }

    return PRO_OK;
}
