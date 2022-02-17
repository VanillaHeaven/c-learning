#ifndef PROCESS_H
#define PROCESS_H

#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define PRO_OK       1
#define PRO_ERR      0
#define SIGNALTERM   TERM
#define SIGNALHUP    HUP

#define pro_signal_helper(n) SIG##n
#define pro_signal_value(n)  pro_signal_helper(n)
#define pro_value_helper(n)  #n
#define pro_value(n)         pro_value_helper(n)

#endif
