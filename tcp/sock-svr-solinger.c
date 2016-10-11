/*
 * sock-clt-solinger.c
 *
 *  Created on: 2016/9/10
 *      Author: Luo Guochun
 */

#include "cmmhdr.h"
#include <getopt.h>

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
    int s = tcp_server(host, port, 128);
    if(s <= 0) {
        printf("create svr failed: host=%s, port=%d\n", host, port);
        exit(0);
    }
    printf("server running: %s:%d\n", host, port);

    while(1) {
    	char cltip[1024] = {0};
    	int cltport = 0;
    	int cltfd = tcp_accept(s, cltip, sizeof(cltip) - 1, &cltport);
    	printf("accept client: %s:%d\n", cltip, cltport);


		while (1) {
			char buf[1024];
			bool ok = false;
			int cnt = tcp_read(cltfd, buf, 1024, true, &ok);
			if (!ok) {
				printf("no ok read %d bytes\n", cnt);
				close(cltfd);
				break;
			}
			printf("read %d bytes\n", cnt);
		}
	}

    return 0;
}
