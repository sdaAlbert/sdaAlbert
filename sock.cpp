#include"Header.h"
#include"Things.h"

//全局变量

string type;

vector<string> word_v;//words

string username_player, username_question_setter;//now username



int getsockv(int state,vector<string>& words, SOCKET clientSocket)//进行词库同步时需要传入一个容器
{
	if (state != WORD_IN)
	{
		cout << "word error " << "\n";
		return -1;
	}
	int accB = 0;
	accB = send(clientSocket, "2", 2, 0);
	if (accB <= 0)
	{
		return -1;
	}
	int count = 0;
	char recvBuf[1024];
	accB = recv(clientSocket, recvBuf, 1024, 0);
	while (accB > 0)
	{
		recvBuf[accB] = '\0';
		string tmpString = recvBuf;
		words.push_back(tmpString);
		count++;
		int okB = 0;
		okB = send(clientSocket, "OK", 2, 0);
		if (okB != 2)
		{
			cout << "server flooded" << "\n";
			closesocket(clientSocket);
			break;
		}
		accB = recv(clientSocket, recvBuf, 1024, 0);
	}
	cout << "word in : " << count << " words" << "\n";
	return 0;
}
int getsockinfo(int state, string& myInfo, SOCKET clientSocket)//其他情况下直接转成字符串传就行
{
	switch (state)
	{
	case SIGN:
	{
		int accB = 0;
		accB = send(clientSocket, "3", 2, 0);
		if (accB <= 0)
		{
			return -1;
		}
		
		int okB = 0;
		char okBuf[5];
		okB = recv(clientSocket, okBuf, 5, 0);
		if (okB != 2)
		{
			cout << "client flooded" << "\n";
			closesocket(clientSocket);
			break;
		}
		
		accB = send(clientSocket, myInfo.c_str(), myInfo.length(), 0);
		if (accB != myInfo.length())
		{
			return -1;
		}
		
		char recvBuf[1024];
		accB = recv(clientSocket, recvBuf, 1024, 0);
		if (accB != 1)
		{
			return -1;
		}
		else
		{
			okB = 0;
			okB = send(clientSocket, "OK", 2, 0);
			if (okB != 2)
			{
				cout << "server flooded" << "\n";
				closesocket(clientSocket);
				return -1;
			};
			recvBuf[accB] = '\0';
			if (recvBuf[0] == '0')cout << "recv error\n";
			else if (recvBuf[0] == '1')cout << "User successfully registers!" << "\n";
			else if (recvBuf[0] == '2')cout << "The Username has been registered.Register failed!" << "\n";
			else cout << "recvBuffer error" << "\n";
			return 0;
		}
		break;
	}
	case LOGIN:
	{
		int accB = 0;
		accB = send(clientSocket, "4", 2, 0);
		if (accB <= 0)
		{
			return -1;
		}
		
		int okB = 0;
		char okBuf[5];
		okB = recv(clientSocket, okBuf, 5, 0);
		if (okB != 2)
		{
			cout << "client flooded" << "\n";
			closesocket(clientSocket);
			break;
		}
		//发送账户类型，用户名
		accB = send(clientSocket, myInfo.c_str(), myInfo.length(), 0);
		if (accB != myInfo.length())
		{
			return -1;
		}
		//接收返回的提示信息
		char recvBuf[1024];
		accB = recv(clientSocket, recvBuf, 1024, 0);
		if (accB <= 0)
		{
			cout << "recv error 03" << "\n";
			return -1;
		}
		else
		{
			recvBuf[accB] = '\0';
			if (recvBuf[0] == '1')return 1;
			else if (recvBuf[0] == '2')return 2;
			else return 0;
		}
		break;
	}
	case GAME:
	{
		int accB = 0;
		
		accB = send(clientSocket, "5", 2, 0);
		if (accB <= 0)
		{
			return -1;
		}
		//等待对方取走状态码并返回确认信号
		int okB = 0;
		char okBuf[5];
		okB = recv(clientSocket, okBuf, 5, 0);
		if (okB != 2)
		{
			cout << "client flooded" << "\n";
			closesocket(clientSocket);
			return -1;
		}
		
		accB = send(clientSocket, myInfo.c_str(), myInfo.length(), 0);
		if (accB != myInfo.length())
		{
			return -1;
		}
		else return 0;
	}
	case PROBLEM:
	{
		int accB = 0;
		accB = send(clientSocket, "6", 2, 0);
		
		if (accB <= 0)
		{
			return -1;
		}
		int okB = 0;
		char okBuf[5];
		okB = recv(clientSocket, okBuf, 5, 0);
		if (okB != 2)
		{
			cout << "client flooded" << "\n";
			closesocket(clientSocket);
			return -1;
		}
		//发送用户名+单词列表
		accB = send(clientSocket, myInfo.c_str(), myInfo.length(), 0);
		if (accB != myInfo.length())
		{
			return -1;
		}
		//接收返回的提示信息
		okB = recv(clientSocket, okBuf, 5, 0);
		if (okB != 2)
		{
			cout << "client flooded" << "\n";
			closesocket(clientSocket);
			return -1;
		}
		else return 0;
	}
	case FIND:
	{
		int accB = 0;
		accB = send(clientSocket, "7", 2, 0);

		if (accB <= 0)
		{
			closesocket(clientSocket);
			return -1;
		}
		int okB = 0;//判断泛洪
		char okBuf[5];
		okB = recv(clientSocket, okBuf, 5, 0);
		if (okB != 2)
		{
			cout << "server flooded" << "\n";
			closesocket(clientSocket);
			return -1;
		};
		accB = send(clientSocket, myInfo.c_str(), myInfo.length(), 0);
		if (accB != myInfo.length())
		{
			closesocket(clientSocket);
			return -1;
		}

		char recvBuf[1024];
		accB = recv(clientSocket, recvBuf, 1024, 0);
		if (accB <= 0)
		{
			closesocket(clientSocket);
			return -1;
		}
		else recvBuf[accB] = '\0';
		okB = send(clientSocket, "OK", 2, 0);
		if (okB != 2)
		{
			cout << "server flooded" << "\n";
			closesocket(clientSocket);
			return -1;
		};
		cout << "rank:  ";
		while (accB > 0)
		{
			string tmpString = recvBuf;
			cout << tmpString << "\n";
			accB = recv(clientSocket, recvBuf, 1024, 0);//列表每行的信息
			if (accB <= 0)
			{
				closesocket(clientSocket);
				return -1;
			}
			else recvBuf[accB] = '\0';
			okB = send(clientSocket, "OK", 2, 0);//发送一个确认信息
			if (okB != 2)
			{
				cout << "server flooded" << "\n";
				closesocket(clientSocket);
				return -1;
			};
		}
		return 0;
	}
	case LOGOUT:
	{
		int accB = 0;
		accB = send(clientSocket, "8", 2, 0);
		if (accB <= 0)
		{
			return -1;
		}
		
		int okB = 0;
		char okBuf[5];
		okB = recv(clientSocket, okBuf, 5, 0);
		if (okB != 2)
		{
			cout << "client flooded" << "\n";
			closesocket(clientSocket);
			break;
		}
		//发送用户名
		accB = send(clientSocket, myInfo.c_str(), myInfo.length(), 0);
		if (accB != myInfo.length())
		{
			cout << "send error" << "\n";
			return -1;
		}
		
		char recvBuf[1024];
		accB = recv(clientSocket, recvBuf, 1024, 0);
		if (accB <= 0)
		{
			cout << "recv error" << "\n";
			return -1;
		}
		else
		{
			recvBuf[accB] = '\0';
			if (recvBuf[0] == '1')return 1;
			else if (recvBuf[0] == '2')return 2;
			else return 0;
		}
		break;
	}

	default:
	{
		cout << "default error" << "\n";
		break;
	}
	}
	return -2;
}
int ok_send(SOCKET sockClient)
{
	int okB = 0;
	char okBuf[5];
	okB = recv(sockClient, okBuf, 5, 0);
	if (okB != 2)
	{
		cout << "client flooded" << "\n";
		closesocket(sockClient);
		return -1;
	}
	return 0;
}

int ok_recv(SOCKET sockClient)
{
	int okB = 0;
	okB = send(sockClient, "OK", 2, 0);
	if (okB != 2)
	{
		cout << "server flooded" << "\n";
		closesocket(sockClient);
		return -1;
	}
	return 0;
}

SOCKET socket_init(SOCKADDR_IN addrServ)
{
	SOCKET clientSocket;
	if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		cerr << "Failed to create socket." << "\n";
	}
	if (connect(clientSocket, (sockaddr*)&addrServ, sizeof(addrServ)) == SOCKET_ERROR) {
		cout << "connect Failed" << "\n";
	}
	else 
		cout << "connect Successfully" << "\n";

	return clientSocket;
}