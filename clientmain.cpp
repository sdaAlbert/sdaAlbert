#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "Header.h"
#include "Things.h"

#pragma comment(lib, "ws2_32.lib") 

const char* ServerIP = "127.0.0.1";
constexpr auto SERVER_PORT = 8888; 

vector<string> word_add;

int main() {
	//设置第一个套接字，建立连接
	WSADATA wsaData;
	WORD wVersionRequested;
	int SocketInit = 1;
	int err;
	wVersionRequested = MAKEWORD(2, 2);
	WSAStartup(wVersionRequested, &wsaData);
	if (SocketInit != 0 && (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2))
	{
		WSACleanup();
		SocketInit = 0;
	}
	if (SocketInit != 0)SocketInit = 1;
	if (SOCKET_ERROR == SocketInit)
		return -1;
	//初始化套接字
	SOCKADDR_IN addrServ;
	addrServ.sin_addr.S_un.S_addr = inet_addr(ServerIP);//设定需要连接的服务器的ip地址
	addrServ.sin_family = AF_INET;
	addrServ.sin_port = htons(8888);//端口

	//读入单词库
	SOCKET clientSocket= socket_init(addrServ);
	Sleep(100);
	err=getsockv(WORD_IN, word_v, clientSocket);
	if (err == -1)cout << "word read fail\n";
	closesocket(clientSocket);
	cout << "\n";

	/*run*/
	int choose, flag;
	while (true)
	{
		word_add.clear();
		
		//system("cls");
		cout << "wwwwwelcome to the death word game!\n"
			<< "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww\n"
			<< "choose the number to order\n"
			<< "1   sign up\n"
			<< "2   log in\n"
			<< "3   quit\n"
			<< "-----------------------------------------------\n"
			<< "now input the number:\n";

		cin >> choose;
		if (choose == 1)
		{
			sign_up(addrServ);
			system("pause");
		}
		else if (choose == 2)
		{

			flag = login(addrServ);

			system("pause");
			if (flag == 0 || flag == 2 || flag == 3)continue;
			system("cls");
			while (true)
			{
				int ch;
				if (type == "p")
				{

					cout << "1   game start\n"
						<< "2    rank\n"
						<< "3   search\n"
						<< "4   logout\n"
						<< "-----------------------------------------------\n"
						<< "now input the number:\n";
					cin >> ch;
					if (ch == 1)
					{
						game_starto(addrServ);
					}
					else if (ch == 2)
					{
						rank_player(addrServ);
					}
					else if (ch == 3)
					{
						search_player(addrServ);
					}
					else if (ch == 4)
					{
						logout(addrServ);//刷
						break;
					}
					else continue;
				}
				else if (type == "q")
				{
					cout << "1   new word question\n"
						 << "2    rank\n"
						 << "3   search\n"
						 << "4   logout\n"
						 << "-----------------------------------------------\n"
						 << "now input the number:\n";
					cin >> ch;
					if (ch == 1)
					{
						new_words(addrServ);
					}
					else if (ch == 2)
					{
						rank_question_setter(addrServ);
					}
					else if (ch == 3)
					{
						search_question_setter(addrServ);
					}
					else if (ch == 4)
					{
						logout(addrServ);
						break;
					}
					else continue;
				}
				system("pause");
			}
		}
		else if (choose == 3)
		{
			
			return 0;
		}
		else
			cout << "wrong input" << "\n";

	}
    
    

    // 关闭套接字，释放资源
    closesocket(clientSocket);

    // 清除 Winsock
    WSACleanup();

    return 0;
}
