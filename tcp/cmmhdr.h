/*
 * cmmhdr.h
 *
 *  Created on: 2016/10/11
 *      Author: Luo Guochun
 */

#ifndef _CMMHDR_H_
#define _CMMHDR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "sock.h"

#define REGISTER_SIGNAL(type, func/*, interupt*/)         \
    do{                                                   \
        if(register_signal(type, func/*, interupt*/) ==   \
                SIG_ERR){                                 \
            printf("register signal %d failed: %s\n",     \
                    type, strerror(errno));               \
            return -1;                                    \
        }                                                 \
    }while(0)



#endif /* _CMMHDR_H_ */
