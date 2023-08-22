#include"Header.h"
#include"Things.h"

void new_words(SOCKADDR_IN addrServ)
{
	bool finished_flag = false;
	string new_word;
	while (!finished_flag)
	{
		cout << "input new word:\n" ;
		cin >> new_word;

		vector<string>::iterator ir;
		ir = find(word_v.begin(), word_v.end(), new_word);
		if (ir == word_v.end())//是个新单词
		{
			word_v.push_back(new_word);
			cout << "new word success：" << word_v.back() << "\n";
			word_add.push_back(new_word);
			
			now_question_setter.inc_word_num();
			now_question_setter.update_EXP(new_word);
			now_question_setter.update_level();
			update_question_setter(addrServ);
		}
		else
		{
			cout << "the word has already existed\n";
		}

		cout << "continue(0) or quit(1) \n";
		cin >> finished_flag;
	}
	print_question_setter();
}

void update_question_setter(SOCKADDR_IN addrServ)
{
	string tmpstring = now_question_setter.show_name()+ "," + to_string(now_question_setter.show_EXP()) + ',' + to_string(now_question_setter.show_level()) + ',' + to_string(now_question_setter.show_word_num());
	for (int i = word_add.size() - 1; i >= 0; i--)
	{
		tmpstring = tmpstring + "," + word_add[i];
	}
	SOCKET sockClient = socket_init(addrServ);
	int flushtag = getsockinfo(PROBLEM, tmpstring, sockClient);
	closesocket(sockClient);
	for (int i = 0; flushtag != 0 && i < 3; i++)
	{
		sockClient = socket_init(addrServ);
		flushtag = getsockinfo(PROBLEM, tmpstring, sockClient);
		closesocket(sockClient);
	}
	if (flushtag == 0)cout << "result upload success" << "\n";
	else cout << "result upload failure" << "\n";
	return;
}