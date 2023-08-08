#include"Header.h"
#include"Things.h"

void search_player(SOCKADDR_IN addrServ)
{
	
	string choice;

	cout << "choose the trait you want to search name" << "\n";
	cin >> choice;
	if (choice == "n")
	{
		string in_name;
		cout << "username:" << "\n";
		cin >> in_name;
		SOCKET sockClient = socket_init(addrServ);
		string tmpString = to_string(3) + "," + in_name;
		getsockinfo(FIND, tmpString, sockClient);
		closesocket(sockClient);

		//findit('p', 'n', 0, in_name);
	}
	else
	{
		cout << "wrong choice\n";
		return;
	}
	getchar();
}
void search_question_setter(SOCKADDR_IN addrServ)
{
	
	string choice;

	cout << "choose the trait you want to search name" << "\n";
	cin >> choice;
	if (choice == "n")
	{
		string in_name;
		cout << "username:" << "\n";
		cin >> in_name;
		SOCKET sockClient = socket_init(addrServ);
		string tmpString = to_string(3) + "," + in_name;
		getsockinfo(FIND, tmpString, sockClient);
		closesocket(sockClient);

		//findit('q', 'n', 0, in_name);
	}
	else
	{
		cout << "wrong choice\n";
		return;
	}
	getchar();
}
void rank_question_setter(SOCKADDR_IN addrServ)
{

	string choice;

	cout << "choose the trait you want to rank name/level/word_num" << "\n";
	cin >> choice;
	if (choice == "n")
	{
		SOCKET sockClient = socket_init(addrServ);
		string tmpString = to_string(2) + ",1" ;
		getsockinfo(FIND, tmpString, sockClient);
		closesocket(sockClient);

		//findit('q', 'n', 0, in_name);
	}
	else if (choice == "l")
	{

		SOCKET sockClient = socket_init(addrServ);
		string tmpString = to_string(2) + ",2" ;
		getsockinfo(FIND, tmpString, sockClient);
		closesocket(sockClient);
		//findit('q', 'l', level_in);
	}
	else if (choice == "w")
	{
		SOCKET sockClient = socket_init(addrServ);
		string tmpString = to_string(2) + ",3" ;
		getsockinfo(FIND, tmpString, sockClient);
		closesocket(sockClient);
		//findit('q', 'w', word_num_in);
	}
	else
	{
		cout << "wrong choice\n";
		return;
	}
}
void rank_player(SOCKADDR_IN addrServ)
{

	string choice;
	cout << "choose the trait you want to rank name/level/pass_num" << "\n";
	cin >> choice;
	if (choice == "n")
	{
		SOCKET sockClient = socket_init(addrServ);
		string tmpString = to_string(1) + ",1";
		getsockinfo(FIND, tmpString, sockClient);
		closesocket(sockClient);
	}
	else if (choice == "l")
	{

		SOCKET sockClient = socket_init(addrServ);
		string tmpString = to_string(1) + ",2";
		getsockinfo(FIND, tmpString, sockClient);
		closesocket(sockClient);
	}
	else if (choice == "p")
	{
		SOCKET sockClient = socket_init(addrServ);
		string tmpString = to_string(1) + ",3";
		getsockinfo(FIND, tmpString, sockClient);
		closesocket(sockClient);
	}
	else
	{
		cout << "wrong choice\n";
		return;
	}
}