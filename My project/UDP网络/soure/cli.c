#include <stdio.h>
#include <winsock2.h>

int main() {

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//创建客户端套接字
	SOCKET client_socket = socket(AF_INET, SOCK_DGRAM, 0);

	//服务器地址信息
	SOCKADDR_IN server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(12345);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	char buff[100];

	while (1) {

		memset(buff, '\0', sizeof buff);

		gets(buff);

		sendto(client_socket, buff, strlen(buff), 0, (SOCKADDR*)&server_addr, sizeof(server_addr));

	}

	closesocket(client_socket);

	WSACleanup();

	return 0;
}
