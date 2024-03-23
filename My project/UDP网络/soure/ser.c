#include <stdio.h>
#include <winsock2.h>

int main() {
	
	WSADATA wsaData;
	WSAStartup( MAKEWORD(2, 2), &wsaData);

	//创建服务端套接字
	SOCKET server_socket = socket(AF_INET, SOCK_DGRAM, 0);

	//服务端地址
	SOCKADDR_IN server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(12345);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	//绑定
	bind(server_socket, (SOCKADDR*)&server_addr, sizeof(server_addr));

	//客户端地址
	SOCKADDR_IN client_addr;
	int client_len = sizeof(client_addr);
	
	char buff[100];

	while (1) {
		
		//清空缓冲区
		memset(buff, '\0', sizeof buff);
		
		recvfrom(server_socket, buff, 100, 0, (SOCKADDR*)&client_addr, &client_len);
		
		printf("%s\n",buff);
		
	}

	closesocket(server_socket);
	
	WSACleanup();
	
	return 0;
}
