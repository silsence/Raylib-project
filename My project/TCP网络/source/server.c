#include <stdio.h>
#include <winsock2.h>

int main(void){
	
	WSADATA wsaData;
	WSAStartup( MAKEWORD(2, 2), &wsaData);
	
	//服务端套接字
	SOCKET server_socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	
	//服务端地址
	SOCKADDR_IN server_addr;
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(12345);
	server_addr.sin_addr.S_un.S_addr=INADDR_ANY;
	
	//绑定服务端套接字到服务端的IP端口
	bind(server_socket,(SOCKADDR*)&server_addr,sizeof(server_addr));
	
	//监听服务端套接字，0:成功,!0:失败
	listen(server_socket,3);
	printf("等待客户端连接:\n");
	
	//客户端地址
	SOCKADDR_IN client_addr;
	int client_len=sizeof(client_addr);
	
	//accept监听服务端套接字，并创建独立套接字，并将客户端的地址保存在client_addr中
	SOCKET client_socket=accept(server_socket,(SOCKADDR*)&client_addr,&client_len);
	//INVALID_SOCKET:无效套接字描述符
	if (client_socket != INVALID_SOCKET) {
		printf("连接成功!\n");
	}
	
	char buff[100];
	
	while(1){
		
		int recv_len;
		
		recv_len = recv(client_socket, buff, 100, 0);
		
		if (strcmp(buff,"quit")==0) {
			break;
		}
		
		if (recv_len != -1)
			printf("客户端信息:%s\n",buff);
		else {
			printf("客户端断开连接!");
			break;
		}
		
	}
	
	closesocket(server_socket);
	closesocket(client_socket);
	
	WSACleanup();
	
	return 0;
}
