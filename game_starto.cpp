#include"Header.h"
#include"Things.h"

int game_starto(SOCKADDR_IN addrServ)
{
	string in_word;
	int tmpEXP=0;
	int capacity = 0,round=1;
	int index = 0;
	capacity = word_v.size();
	if (!capacity) { cout << "run out of words!please add words first\n"; return 0; }
	//排序单词长度
	sort(word_v.begin(), word_v.end(), [](const string& a1, const string& a2) {return a1.size() < a2.size(); });
	
	cout << "how many round you want" <<"\n";
	cin >> round;
	for (int i=0;i<round;i++)
	{
		cout << "\n\nround " << i+1 << "\n";
		cout << "This word will disappear in 3s please remember:\n";

		srand(time(NULL));
		index = capacity/round*i+ rand() % (capacity/round);
		reround:cout << word_v.at(index)<<"       3s";

		Sleep(1000);
		cout << "\033[2K\r";
		cout << word_v.at(index) << "       2s";
		Sleep(1000);
		cout << "\033[2K\r"; 
		cout << word_v.at(index) << "       1s";
		Sleep(1000);
		cout << "\033[2K\r";
		cout << "please repeat the word:";

		auto start = std::chrono::high_resolution_clock::now();
		cin >> in_word;
		auto end = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
		cout << "using Time: " << duration.count() << " ms." << "\n";

		if (in_word == word_v.at(index))
		{
			cout << "bingo\n";
			tmpEXP=(i + 1)* duration.count() / 1000;
			now_player.update_EXP((i + 1) * duration.count() / 1000);
			now_player.update_level();
			now_player.inc_pass_num();
			update_player(addrServ,tmpEXP);

		}
		else
		{
			cout << "wrong words，mission failed let's do it again:\n" ;
			goto reround;
		}
	}
	print_player();
	cout << "game over" << "\n";
	return 0;
}

void update_player(SOCKADDR_IN addrServ,int tmpEXP)
{
	SOCKET sockClient = socket_init(addrServ);
	string tmpstring = now_player.show_name() + "," + to_string(tmpEXP);
	int flushtag = -1;
	flushtag = getsockinfo(GAME, tmpstring, sockClient);
	closesocket(sockClient);
	for (int i = 0; i < 2&&flushtag != 0; i++)
	{
		sockClient = socket_init(addrServ);
		flushtag = getsockinfo(GAME, tmpstring, sockClient);
		closesocket(sockClient);
	}
	if (flushtag == 0)cout << "Result Upload Success" << "\n";
	else cout << "Result Upload Failure" << "\n";
	return;
}