#ifdef _WIN32

#include <windows.h>
#pragma comment(lib, "wsock32.lib")

#endif
#ifdef __linux__

#include <stdio.h>
#include <sys/socket.h>

#endif

#include <iostream>
#include <string>

int main() {
    //初始化 DLL
    WSADATA wsaData;
    WSAStartup( MAKEWORD(2, 2), &wsaData);


    // AF_INET = IPv4
    // SOCK_DGRAM = UDP
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    // 檢查是否建立成功
    if (socket_fd < 0) {
        std::cout << "Fail to create a socket." << std::endl;
    }

    //繫結套接字
    sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));  //每個位元組都用0填充
    sockAddr.sin_family = PF_INET;  //使用IPv4地址
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具體的IP地址
    sockAddr.sin_port = htons(1234);  //埠
    bind(socket_fd, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

    //進入監聽狀態
    listen(socket_fd, 20);

    //接收客戶端請求
    SOCKADDR clntAddr;
    int nSize = sizeof(SOCKADDR);
    SOCKET clntSock = accept(socket_fd, (SOCKADDR*)&clntAddr, &nSize);

     //向客戶端傳送資料
    std::string str = "Hello World!";
    send(clntSock, str.c_str(), str.length()+sizeof(char), 0);


    // 根據 socker_fd 關閉剛剛創立的 socket
    closesocket(socket_fd);
    closesocket(clntSock);

    //終止 DLL 的使用
    WSACleanup();

    return 0;
}