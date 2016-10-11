/*
 * util.h
 *
 *  Created on: 2016/10/11
 *      Author: Luo Guochun
 */

#ifndef _UTIL_H_
#define _UTIL_H_

typedef void sigfunc(int);
sigfunc *register_signal(int signo, sigfunc * func);



#endif /* _UTIL_H_ */
