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

int main(){
    //初始化DLL
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    //建立套接字
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

    //向伺服器發起請求
    sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));  //每個位元組都用0填充
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sockAddr.sin_port = htons(1234);
    connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

    //接收伺服器傳回的資料
    char szBuffer[MAXBYTE] = {0};
    recv(sock, szBuffer, MAXBYTE, 0);

    //輸出接收到的資料
    printf("Message form server: %s\n", szBuffer);

    //關閉套接字
    closesocket(sock);

    //終止使用 DLL
    WSACleanup();

    return 0;
}