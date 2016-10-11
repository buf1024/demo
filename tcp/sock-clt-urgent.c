/*
 * sock-clt-urgent.c
 *
 *  Created on: 2016/10/11
 *      Author: Luo Guochun
 */

#include "cmmhdr.h"

int main(int argc, char **argv)
{
    extern char *optarg;

    int optch;
    char optstring[] = "h:p:";

    char host[1024] = {0};
    int port = 0;
    //读取命令行参数
    while ((optch = getopt(argc, argv, optstring)) != -1) {
        switch (optch) {
        case 'h':
            strncpy(host, optarg, sizeof(host) - 1);
            break;
        case 'p':
            port = atoi(optarg);
            break;
        default:
            printf("%s -h <ip/host> -p <port>\n", argv[0]);
            exit(0);
        }
    }
    if(strlen(host) == 0 || port <= 0) {
        printf("host/ip/port is not valid: host=%s, port=%d\n", host, port);
		printf("%s -h <ip/host> -p <port>\n", argv[0]);
        exit(0);
    }

    int s = tcp_connect(host, port);
    if(s <= 0) {
        printf("connect to host failed: host=%s, port=%d\n", host, port);
        exit(0);
    }

    printf("socket connect: host=%s, port=%d\n", host, port);
    printf("sleep for seconds\n");

    char buf[1024] = {0};
    strcpy(buf, "hello");

    bool ok = false;
    tcp_write(s, buf, strlen(buf), true, &ok);
    if(!ok) {
    	printf("write failed.\n");
    	close(s);
    	return 0;
    }
    sleep(1);
    strcpy(buf, "kill me!");
	if (send(s, buf, strlen(buf), MSG_OOB) <= 0) {
    	printf("write ugent data failed.\n");
    	close(s);
    	return 0;
	}

    sleep(2);
    close(s);

    return 0;
}

