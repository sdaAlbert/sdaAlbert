#include"Header.h"
#include"Things.h"
#include"Class.h"
player now_player;
question_setter now_question_setter;

void sign_up(SOCKADDR_IN addrServ)
{
	string type;
	string a;
	string name;
	cout << "Are you a player(p) or a question setter(q)?\n";
	cin >> type;
	cout << "username:\n";
	cin >> name;
	SOCKET sockClient = socket_init(addrServ);
	if (type == "p")a =  "1," + name;
	if (type == "q")a = "2," + name;
	getsockinfo(SIGN, a, sockClient);
	closesocket(sockClient);

	cin.clear();
	cin.ignore(INT_MAX, '\n');//清除输入缓冲区的当前行 
}

int login(SOCKADDR_IN addrServ)
{
	string name;
	int lr;
	cout << "Are you a player(p) or a question setter(q)?\n";
	cin>>type;
	cout << "username:\n";
	cin>>name;
	if (type == "p")
	{
		SOCKET sockClient = socket_init(addrServ);
		string a = "1,";
		a += name;
		lr = getsockinfo(LOGIN,a , sockClient);
		closesocket(sockClient);

		if (lr == 0)
		{
			cout << "socket error\n";
		}
		else if (lr == 1)
		{
			cout << "player log in success\nWelcome, " + name + "!\n";
			player p_tmp(name);
			now_player = p_tmp;
		}
		else if (lr == 2)
		{
			cout << "not found p\n";
		}
		else if (lr == 3)
		{
			cout << "already login!\n";
		}
	}
	if (type == "q")
	{
		SOCKET sockClient = socket_init(addrServ);
		string a = "2,";
		a += name;
		lr = getsockinfo(LOGIN,a, sockClient);
		closesocket(sockClient);

		if (lr == 0)
		{
			cout << "socket error\n";
		}
		else if (lr == 1)
		{
			cout << "question_setter log in success\nWelcome, " + name + "!\n";
			question_setter q_tmp(name);
			now_question_setter = q_tmp;
		}
		else if (lr == 2)
		{
			cout << "not found q\n";
		}
		}
	return lr;
}

void logout(SOCKADDR_IN addrServ)
{

	if (type == "p")
	{
		SOCKET sockClient = socket_init(addrServ);
		string a = now_player.show_name();
		int logout_result = getsockinfo(LOGOUT, a, sockClient);
		if (logout_result == 2)
		{
			cout << "not found this player\n";
			return;
		}
		print_player();
		cout << "log out\n";
	}
	else if (type == "q")
	{
		print_question_setter();

		cout << "log out\n";
	}
	else
	{
		cout << "not right type please choose p or q\n";
	}
	getchar();
}

void print_player()
{
	cout << "name:" << now_player.show_name() << '\t'
		<< "EXP:" << now_player.show_EXP() << '\t'
		<< "level:" << now_player.show_level() << '\t'
		<< "the passed num:" << now_player.show_pass_num() << "\n";
}
void print_question_setter()
{
	cout << "name:" << now_question_setter.show_name() << '\t'
		<< "EXP:" << now_question_setter.show_EXP() << '\t'
		<< "level:" << now_question_setter.show_level() << '\t'
		<< "words num:" << now_question_setter.show_word_num() << "\n";
}