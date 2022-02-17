/****************************************
*
*  unix 信号处理练习
*  要求对标准信号能捕捉处理
*
*****************************************/
#include "process.h"


void signal_handler(int signo);
void init_signal();
void cycle();


sig_atomic_t pro_quit = 0;
sig_atomic_t pro_hup  = 0;


typedef struct {
    int signo;
    char *signame;
    void (*sighandler)(int signo);
} signal_t;


signal_t signals[] = {
    { pro_signal_value(SIGNALTERM),
      "SIG" pro_value(SIGNALTERM),
      signal_handler },

    { pro_signal_value(SIGNALHUP),
      "SIG" pro_value(SIGNALHUP),
      signal_handler },

    { 0, NULL, NULL }
};

int main(int argc, char *const *argv) {

    init_signal();

    cycle();

    return 0;
}


void signal_handler(int signo) {
    signal_t *sg = signals;

    for (; sg->signame != NULL; sg++) {
        if (sg->signo == signo) {
            break;
        }
    }

    switch (sg->signo) {

    case pro_signal_value(SIGNALTERM):
        pro_quit = 1;
        break;

    case pro_signal_value(SIGNALHUP):
        pro_hup = 1;
        break;

    default:
        break;
    }

    return;
}


void init_signal() {

    struct sigaction sa;
    signal_t *sg = signals;

    for(;sg->signame != NULL; sg++) {
        sa.sa_handler = sg->sighandler;
        sigemptyset(&sa.sa_mask);
        sigaction(sg->signo, &sa, NULL);
    }
}


void cycle() {

    for(;;) {
        if (pro_quit) {
            printf("====== quit\n");
            pro_quit = 0;
            return;
        }

        if (pro_hup) {
            printf("====== hup\n");
            pro_hup = 0;
            continue;
        }
    }

    return;
}
