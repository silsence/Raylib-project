#include <stdio.h>
#include <winsock2.h>

int main(void){
	
	WSADATA wsaData;
	WSAStartup( MAKEWORD(2, 2), &wsaData);
	
	//创建客户端套接字
	SOCKET client_socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	
	//创建服务端地址
	SOCKADDR_IN server_addr;
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(12345);
	server_addr.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
	
	//将客户端套接字连接到指定的服务端地址
	connect(client_socket,(SOCKADDR*)&server_addr,sizeof(server_addr));
	
	char buff[100];
	
	while(1){
		
		gets(buff);
		send(client_socket,buff,100,0);
	}
	
	closesocket(client_socket);
	
	WSACleanup();
	
	return 0;
}
