// 17monipdb.dat from ipip.net

#include <stdlib.h>

#include "dpdk-simple-web/simple-web-server.c"
#include "ipip.h"

#include "ipip.c"

#define MAXLEN 1024

const char *http_head =
    "HTTP/1.0 200 OK\r\nConnection: close\r\nContent-Type: text/html; charset=UTF-8\r\nServer: dpdk web server by james@ustc.edu.cn, data from ipip.net\r\n\r\n";

static inline int user_init_func(int argc __attribute__ ((unused)), char *argv[]
				 __attribute__ ((unused)))
{
	printf("user_init_func: argc=%d\n", argc);
	printf("Version: %s\n", VERSION);
	if (init("17monipdb.dat") != 1) {
		printf("init 17monipdb.dat error, do you put 17monipdb.dat in current dir?\n");
		exit(-1);
	}
	return 0;
}

// #define DEBUGHTTP

static inline int process_http(int ip_version, void *iph __attribute__ ((unused)),
			       struct tcp_hdr *tcph __attribute__ ((unused)),
			       unsigned char *http_req __attribute__ ((unused)),
			       int req_len __attribute__ ((unused)),
			       unsigned char *http_resp __attribute__ ((unused)),
			       int *resp_len, int *resp_in_req)
{
#ifdef DEBUGHTTP
	printf("http req payload is: ");
	int i;
	for (i = 0; i < req_len; i++) {
		unsigned char c = *(http_req + i);
		if ((c > 31) && (c < 127))
			printf("%c", c);
		else
			printf(".");
	}
	printf("\n");
	printf("max-http-repsone len: %d\n", *resp_len);
#endif
	http_req[req_len] = 0;
	int len = 0;
	char result[128];

	*resp_in_req = 1;	// write response to http_req, no memcpy needed
	if (memcmp(http_req, "GET /", 5) != 0)
		return 0;
	if (memcmp(http_req + 5, "favicon.ico", 11) == 0)
		len = snprintf((char *)http_req, *resp_len,
			       "HTTP/1.0 404 OK\r\nConnection: close\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n");
	else if (*(http_req + 5) == ' ') {	//   GET /, show ip and desc
		char ip[100];
		if (ip_version == 4)
			strncpy(ip, INET_NTOA(((struct ipv4_hdr *)iph)->src_addr), 20);
		else
			inet_ntop(AF_INET6, &((struct ipv6_hdr *)iph)->src_addr, ip, 100);
		find(ip, result, 128);
		len = snprintf((char *)http_req, *resp_len, "%s%s %s\r\n", http_head, ip, result);
	} else if (*(http_req + 5) >= '0' && *(http_req + 5) <= '9') {	// GET /IP, show ip desc
		find((const char *)http_req + 5, result, 128);
		if (result[0])
			len = snprintf((char *)http_req, *resp_len, "%s%s\r\n", http_head, result);
		else
			len = snprintf((char *)http_req, *resp_len, "%sNULL\r\n", http_head);
	} else
		len = snprintf((char *)http_req, *resp_len,
			       "%s%s\r\n", http_head,
			       "使用方式: <br>http://serverip/ 显示本机IP地址和信息<br>http://serverip/IP地址 显示IP地址的信息<p>"
			       "IP地址数据库来自<a href=http://ipip.net>http://ipip.net</a>免费版，最后更新时间20180101<br>"
			       "感谢北京天特信科技有限公司<p><a href=https://github.com/bg6cq/ipdesc-dpdk>https://github.com/bg6cq/ipdesc-dpdk</a><br>james@ustc.edu.cn 2018.01.06");
	if (len < *resp_len)
		*resp_len = len;
#ifdef DEBUGHTTP
	printf("resp_len %d\n", *resp_len);
#endif
	return 1;
}
