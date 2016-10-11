/*
 * sock-svr-urgent.c
 *
 *  Created on: 2016/10/11
 *      Author: Luo Guochun
 */

#include "cmmhdr.h"
#include <getopt.h>
#include <signal.h>
#include <netinet/tcp.h>

int g_clt_fd = -1;
void sigurgent(int signo) {
	char buf[1024] = { 0 };
	printf("SIGURG received\n");
	int cnt = recv(g_clt_fd, buf, sizeof(buf) - 1, MSG_OOB);
	if (cnt > 0) {
		printf("recevie urgent data: %s, count = %d\n", buf, cnt);
		//close(g_clt_fd);
		//g_clt_fd = -1;
	}
	close(g_clt_fd);
	g_clt_fd = -1;
}

int main(int argc, char **argv) {
	extern char *optarg;

	int optch;
	char optstring[] = "h:p:";

	char host[1024] = { 0 };
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

	if (strlen(host) == 0 || port <= 0) {
		printf("host/ip/port is not valid: host=%s, port=%d\n", host, port);
		printf("%s -h <ip/host> -p <port>\n", argv[0]);
		exit(0);
	}
	int s = tcp_server(host, port, 128);
	if (s <= 0) {
		printf("create svr failed: host=%s, port=%d\n", host, port);
		exit(0);
	}
	printf("server running: %s:%d\n", host, port);

	REGISTER_SIGNAL(SIGURG, sigurgent);

	int yes = 1;
	/* Make sure connection-intensive things like the redis benckmark
	 * will be able to close/open sockets a zillion of times */
	if (setsockopt(s, SOL_SOCKET, SO_OOBINLINE, &yes, sizeof(yes)) == -1) {
		printf("setsockopt SO_REUSEADDR: %s", strerror(errno));
		return -1;
	}

	struct linger l = {0};
	l.l_onoff = 0;
	if (setsockopt(s, SOL_SOCKET, SO_LINGER, &l, sizeof(l)) == -1) {
		printf("setsockopt SO_REUSEADDR: %s", strerror(errno));
		return -1;
	}

	while (1) {
		char cltip[1024] = { 0 };
		int cltport = 0;
		g_clt_fd = tcp_accept(s, cltip, sizeof(cltip) - 1, &cltport);
		printf("accept client: %s:%d\n", cltip, cltport);

		fcntl(g_clt_fd, F_SETOWN, getpid());

		while (1) {
			if (g_clt_fd <= 0) {
				break;
			}
			char buf[1024] = {0};
			bool ok;
			int cnt = tcp_read(g_clt_fd, buf, 5, true, &ok);
			if (!ok) {
				printf("not ok read %d bytes, %s\n", cnt, buf);
				close(g_clt_fd);
				break;
			}
			printf("read %d bytes, %s\n", cnt, buf);

		}
	}

	return 0;
}
