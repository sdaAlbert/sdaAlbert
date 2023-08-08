#include"Header.h"
#include"Class.h"
#include"Things.h"
extern HANDLE hMutex;

extern vector<SOCKET> socket_pool;

extern vector<player> all_player;//player

extern vector<player> online_player;//online

extern vector<question_setter> all_question_setter;//question_setter

extern vector<string> word_v;//words

void getsockinfo()
{

	Sleep(100);
	WaitForSingleObject(hMutex, INFINITE);
	SOCKET now_sock = socket_pool.back();

	char recvBuf[512];
	int accurateStateBytes = recv(now_sock, recvBuf, MaxSize, 0);
	if (accurateStateBytes != 2)
	{
		cout << "recive error" << "\n";
		closesocket(now_sock);
		return;
	}
	int state = (int)(recvBuf[0] - '0');
	switch (state)
	{
	case WORD_IN:
	{
		int acB = 0;
		for (unsigned int i = 0; i < word_v.size(); i++)
		{
			acB = send(now_sock, word_v[i].c_str(), word_v[i].length(), 0);
			if (acB != word_v[i].length())
			{
				cout << "word eroor" << "\n";
				closesocket(now_sock);
				return;
			}
			int okB = 0;
			char okBuf[5];
			okB = recv(now_sock, okBuf, 5, 0);
			if (okB != 2)
			{
				cout << "client flooded" << "\n";
				closesocket(now_sock);
				break;
			}
		}
		cout << "word input success" << "\n";
		cout << now_sock << "has closed" << "\n";
		closesocket(now_sock);
		break;
	}
	case SIGN:
	{
		int okB = 0;
		okB = send(now_sock, "ok", 2, 0);
		if (okB != 2)
		{
			cout << "server flooded" << "\n";
			closesocket(now_sock);
			break;
		};
		int acB = recv(now_sock, recvBuf, MaxSize, 0);
		if (acB <= 0)
		{
			closesocket(now_sock);
			return;
		}
		else recvBuf[acB] = '\0';

		string tmpString = recvBuf;
		cout << tmpString;
		vector<string>tmp2;
		string_split(tmpString, tmp2, ",");
		
		int ret_flag = sign_up(tmp2);
		if (ret_flag == 0 || ret_flag == 1 || ret_flag == 2)
		{
			tmpString = std::to_string(ret_flag).c_str();
			acB = send(now_sock, tmpString.c_str(), tmpString.length(), 0);
			Sleep(100);
			if (acB != tmpString.length())
			{
				closesocket(now_sock);
				return;
			}
		}
		okB = 0;
		char okBuf[5];
		okB = recv(now_sock, okBuf, 5, 0);
		if (okB != 2)
		{
			cout << "client flooded" << "\n";
			closesocket(now_sock);
			break;
		}
		cout << now_sock << "has closed" << "\n";
		closesocket(now_sock);
		break;
	}
	case LOGIN:
	{
		int okB = 0;
		okB = send(now_sock, "ok", 2, 0);
		if (okB != 2)
		{
			cout << "Server Flooded" << "\n";
			closesocket(now_sock);
			break;
		};
		int acB = recv(now_sock, recvBuf, MaxSize, 0);
		if (acB <= 0)
		{
			closesocket(now_sock);
			return;
		}
		else recvBuf[acB] = '\0';

		string tmpString = recvBuf;
		vector<string>tmp2;
		string_split(tmpString, tmp2, ",");
		int logintag = login(tmp2);
		tmpString = std::to_string(logintag).c_str();
		
		acB = send(now_sock, tmpString.c_str(), tmpString.length(), 0);
		cout << now_sock << "has closed" << "\n";
		closesocket(now_sock);
		break;
	}
	case P_UPDATE:
	{
		int okB = 0;
		okB = send(now_sock, "ok", 2, 0);
		if (okB != 2)
		{
			cout << "server flooded" << "\n";
			closesocket(now_sock);
			break;
		};
		int acB = recv(now_sock, recvBuf, MaxSize, 0);
		if (acB <= 0)
		{
			closesocket(now_sock);
			break;
		}
		else recvBuf[acB] = '\0';
		string tmpString = recvBuf;
		vector<string>tmp2;
		string_split(tmpString, tmp2, ",");
		int flushtag = update_player(tmp2);
		if (flushtag == 1)cout << "player update succeeded." << "\n";
		else cout << "player update error" << "\n";
		closesocket(now_sock);
		break;
	}
	case Q_UPDATE:
	{
		int okB = 0;
		okB = send(now_sock, "ok", 2, 0);
		if (okB != 2)
		{
			cout << "server flooded" << "\n";
			closesocket(now_sock);
			break;
		};
		int acB = recv(now_sock, recvBuf, MaxSize, 0);
		if (acB <= 0)
		{
			closesocket(now_sock);
			break;
		}
		else recvBuf[acB] = '\0';
		vector<string> wordAddList;
		string tmpString = recvBuf;
		string_split(tmpString, wordAddList, ",");
		string name = wordAddList[0];
		wordAddList.erase(wordAddList.begin());
		int tester_flag = update_question_setter(name, wordAddList);
		if (tester_flag != 1)
		{
			closesocket(now_sock);
			break;
		}
		else cout << "question setter update succeed" << "\n";
		okB = send(now_sock, "ok", 2, 0);
		if (okB != 2)
		{
			cout << "server flooded" << "\n";
			closesocket(now_sock);
		};
		break;
	}
	case FIND:
	{
		int okB = 0;
		okB = send(now_sock, "ok", 2, 0);
		if (okB != 2)
		{
			cout << "server flooded" << "\n";
			closesocket(now_sock);
			break;
		};
		int acB = recv(now_sock, recvBuf, MaxSize, 0);
		if (acB <= 0)
		{
			closesocket(now_sock);
			break;
		}
		else recvBuf[acB] = '\0';
		string tmpString = recvBuf;
		vector<string> tmpInfo;
		string_split(tmpString, tmpInfo, ",");
		if (tmpInfo.size() != 2)
		{
			closesocket(now_sock);
			break;
		}
		searchmode(tmpInfo);
		acB = send(now_sock, tmpInfo[0].c_str(), tmpInfo[0].length(), 0);
		if (acB <= 0)
		{
			closesocket(now_sock);
			break;
		}
		char okBuf[5];
		okB = recv(now_sock, okBuf, 5, 0);
		if (okB != 2)
		{
			cout << "client flooded" << "\n";
			closesocket(now_sock);
			break;
		}
		for (unsigned int i = 1; i < tmpInfo.size(); i++)
		{
			acB = send(now_sock, tmpInfo[i].c_str(), tmpInfo[i].length(), 0);
			if (acB <= 0)
			{
				closesocket(now_sock);
				break;
			}
			char okBuf[5];
			okB = recv(now_sock, okBuf, 5, 0);
			if (okB != 2)
			{
				cout << "client flooded" << "\n";
				closesocket(now_sock);
				break;
			}
		}
		cout << "search succeed" << "\n";
		closesocket(now_sock);
		break;
	}
	case LOGOUT:
	{
		int okB = 0;
		okB = send(now_sock, "ok", 2, 0);
		if (okB != 2)
		{
			cout << "server flooded" << "\n";
			closesocket(now_sock);
			break;
		};
		int acB = recv(now_sock, recvBuf, MaxSize, 0);
		if (acB <= 0)
		{
			closesocket(now_sock);
			return;
		}
		else recvBuf[acB] = '\0';

		string tmpString = recvBuf;
		vector<string>tmp2;
		string_split(tmpString, tmp2, ",");
		int logout_flag = logout(tmp2);
		tmpString = std::to_string(logout_flag).c_str();

		acB = send(now_sock, tmpString.c_str(), tmpString.length(), 0);
		cout << now_sock << "has closed" << "\n";
		closesocket(now_sock);
		break;
	}
	default:
	{
		cout << "error default" << "\n";
		break;
	}
	closesocket(now_sock);
	cout << now_sock << "has closed" << "\n";
	return;
	}
}

