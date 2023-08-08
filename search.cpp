#include"Header.h"
#include"Things.h"


void searchmode(vector<string> &tmpInfo)
{
	int firsta = atoi(tmpInfo[0].c_str());
	if (firsta == 0)
	{
		cout << "search err " << "\n";
		return;
	}
	string seconda = tmpInfo[1];//firsta为1或2时，seconda选类型
	string tmpString;
	tmpInfo.clear();
	switch (firsta)
	{
	case 1:
	{
		tmpInfo.push_back("Name\t\tLevel\t\tPass_Num\t\tExp\n");

		firsta = atoi(seconda.c_str());
		cout << firsta;
		if (firsta == 3)
			sort(all_player.begin(), all_player.end(), [](const player& p1, const player& p2) {return p1.show_pass_num() > p2.show_pass_num(); });
		else if (firsta == 2)
			sort(all_player.begin(), all_player.end(), [](const man& p1, const man& p2) {return p1.show_level() > p2.show_level(); });
		else if (firsta == 1)
			sort(all_player.begin(), all_player.end(), [](const man& p1, const man& p2) { return p1.show_name() > p2.show_name(); });
		else
			cout << "player search error" << "\n";
		for (unsigned int i = 0; i < all_player.size(); i++)
		{
			tmpString = all_player[i].show_name() + "\t\t" + std::to_string(all_player[i].show_level())
				+ "\t\t" + std::to_string(all_player[i].show_pass_num()) + "\t\t" + std::to_string(all_player[i].show_EXP()) + "\n";
			tmpInfo.push_back(tmpString);
		}
		break;
	}
	case 2:
	{
		tmpInfo.push_back("Name\t\tLevel\t\tWord_Num\n");

		firsta = atoi(seconda.c_str());
		if (firsta == 3)
			sort(all_question_setter.begin(), all_question_setter.end(), [](const question_setter& p1, const question_setter& p2) {return p1.show_word_num() > p2.show_word_num(); });
		else if (firsta == 2)
			sort(all_question_setter.begin(), all_question_setter.end(), [](const man& p1, const man& p2) {return p1.show_level() > p2.show_level(); });
		else if (firsta == 1)
			sort(all_question_setter.begin(), all_question_setter.end(), [](const man& p1, const man& p2) { return p1.show_name() > p2.show_name(); });
		else
			cout << "question query error" << "\n";
		for (unsigned int i = 0; i < all_question_setter.size(); i++)
		{
			tmpString = all_question_setter[i].show_name() + "\t\t" + std::to_string(all_question_setter[i].show_level())
				+ "\t\t" + std::to_string(all_question_setter[i].show_word_num()) + "\n";
			tmpInfo.push_back(tmpString);
		}

		break;
	}
	case 3://firsta为3时，seconda为用户名
	{
		vector<player>::iterator playerIter = all_player.begin();
		for (; playerIter != all_player.end(); playerIter++)
		{
			if (playerIter->show_name() == seconda)
			{
				tmpInfo.push_back("PlayerInfo:\nName\t\tLevel\t\tpass_num\t\tExp\n");
				tmpInfo.push_back(playerIter->show_name() + "\t\t" + std::to_string(playerIter->show_level()) + "\t\t"
					+ std::to_string(playerIter->show_pass_num()) + "\t\t" + std::to_string(playerIter->show_EXP()) + "\n");
				break;
			}
		}
		vector<question_setter>::iterator Iter = all_question_setter.begin();
		for (; Iter != all_question_setter.end(); Iter++)
		{
			if (Iter->show_name() == seconda)
			{
				tmpInfo.push_back("testerInfo:\nName\t\tLevel\t\tword_num\n");
				tmpInfo.push_back(Iter->show_name() + "\t\t" + std::to_string(Iter->show_level()) + "\t\t"
					+ std::to_string(Iter->show_word_num()) + "\n");
				break;
			}
		}
		if (playerIter == all_player.end() && Iter == all_question_setter.end())
			tmpInfo.push_back("This user does not exist.\n");
		break;
	}
	default:
		break;
	}
}