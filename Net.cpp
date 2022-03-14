#include"Net.h"

int    socket_fd, connect_fd;
struct sockaddr_in servaddr;
char buff[1024];
int    n;

/// <summary>
/// 网络套接字初始化
/// </summary>
/// <returns>成功返回1</returns>
int Net_init() {

	//创建socket
	if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		printf("create socket error:%s(error:%d)\n", strerror(errno), errno);
		exit(0);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(DEFAULT_PORT);

	//bind绑定
	if (bind(socket_fd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1) {
		printf("bind socket error: %s(errno: %d)\n", strerror(errno), errno);
		exit(0);
	}

	return 1;
}

/// <summary>
/// 开启网络监听
/// </summary>
/// <returns>成功返回1</returns>
int Net_listen() {
	if (listen(socket_fd, 10) == -1) {
		printf("listen socket error!\n");
		exit(0);
	}
	else {
		printf("======waiting for client's request======\n");
		return 1;
	}
}

int Net_accept() {
	if ((connect_fd = accept(socket_fd, (struct sockaddr*)NULL, NULL)) == -1) {
		printf("accept soccket error\n");
		return 0;
	}
	else return 1;
}

char* Net_recv(int *num) {
	n = recv(connect_fd, buff, MAXLINE, 0);
	*num = n;
	buff[n] = '\0';
	return buff;
}

void Net_send(char *sendbuff) {
	int pid = fork();
	if (pid==0) { //创建子线程发送
		if (send(connect_fd, sendbuff, strlen(sendbuff), 0) == -1)	
			perror("send error");
		exit(0);
	}
	else {
		waitpid(pid, NULL, 0);
	}
}

int Net_connect_close() {
	close(connect_fd);
	return 1;
}

int Net_socket_close() {
	close(socket_fd);
	return 1;
}

