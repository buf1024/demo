/*
 * util.c
 *
 *  Created on: 2016/10/11
 *      Author: Luo Guochun
 */

#include <signal.h>
#include <unistd.h>

#include "util.h"

sigfunc *register_signal(int signo, sigfunc * func)
{
    struct sigaction act, oact;
    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    if (sigaction(signo, &act, &oact) < 0)
        return SIG_ERR;

    return oact.sa_handler;
}
