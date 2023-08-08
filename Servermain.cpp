#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include"Header.h"
#include"Things.h"

#pragma comment(lib, "ws2_32.lib")

vector<SOCKET> socket_pool;


int main() {

    /*initialize*/
    srand((unsigned int)time(NULL));
    read_words();
    read_player();
    read_question_setter();
    user_player = all_player.end();
    user_question_setter = all_question_setter.end();

    WORD wVersionRequested;
    WSADATA wsaData;
    int err;
    int sockInit = 0;
    wVersionRequested = MAKEWORD(2, 2);
    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0)
    {
        sockInit = 0;
    }
    else if (LOBYTE(wsaData.wVersion) != 2 ||
        HIBYTE(wsaData.wVersion) != 2)
    {
        WSACleanup();
        sockInit = 0;
    }
    if (sockInit != 0)
        sockInit = 1;
    SOCKADDR_IN addrServer;
    addrServer.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(8888);

    SOCKET sockServ = socket(AF_INET, SOCK_STREAM, 0);    
    bind(sockServ, (SOCKADDR*)&addrServer, sizeof(SOCKADDR)); 
    listen(sockServ, 5);

    std::cout << "Server started. "<< "\n";

    int len = sizeof(SOCKADDR);
    SOCKADDR_IN addrClient;

        while (1)
        {
            SOCKET sockClient = accept(sockServ, (SOCKADDR*)&addrClient, &len); //到新的连接出现阻塞调用进程
            if (sockClient == INVALID_SOCKET)
            {
                cout << "acception failed" << "\n";
                Sleep(1000);
                continue;
            }
            socket_pool.push_back(sockClient);
            cout << "new thread" << "\n";
            HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)getsockinfo, (LPVOID)NULL, 0, 0);
        }

        // 关闭客户端套接字，释放资源
        std::cout << "Client disconnected." << "\n";

        // 清除 Winsock
        WSACleanup();

    return 0;
}
