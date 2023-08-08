#include"Header.h"
#include"Things.h"

using namespace std;

void print_player()
{
	cout << "name:" << user_player->show_name() << '\t'
		<< "EXP:" << user_player->show_EXP() << '\t'
		<< "level:" << user_player->show_level() << '\t'
		<< "the passed num:" << user_player->show_pass_num() << "\n";
}
void print_question_setter()
{
	cout << "name:" << user_question_setter->show_name() << '\t'
		<< "EXP:" << user_question_setter->show_EXP() << '\t'
		<< "level:" << user_question_setter->show_level() << '\t'
		<< "words num:" << user_question_setter->show_word_num() << "\n";
}
int update_player(vector<string> tmp2)
{
	string name = tmp2[0];
	int EXP_add= atoi(tmp2[1].c_str());

	vector<player>::iterator playerIter = all_player.begin();
	for (; playerIter != all_player.end();)
	{
		if (playerIter->show_name() == name)
		{
			user_player = playerIter;
			user_player->update_EXP(EXP_add);
			user_player->update_level();
			user_player->inc_pass_num();
			
			break;
		}
		else
			playerIter++;
	}
	vector<player>::iterator iter_p;
	fstream f_player("player.csv", ios::out);
	for (iter_p = all_player.begin(); iter_p != all_player.end(); iter_p++)
	{
		f_player << iter_p->show_name() << ',' << iter_p->show_EXP() << ',' << iter_p->show_level() << ',' << iter_p->show_pass_num() << "\n";
	}
	return 1;
}