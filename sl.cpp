#include"Header.h"
#include"Things.h"

int sign_up(vector<string>& tmppaper)
{
	if (tmppaper[0] == "1")
	{
		player p(tmppaper[1]);
			bool user_existed = false;
			for (auto &iter : all_player)
			{
				if (iter.show_name() == p.show_name())
				{
					user_existed = true;
				}
			}
			if (user_existed)
			{
				cout << "user is existed,please login" << "\n";
				return 2;
			}

			all_player.push_back(p);

			fstream f_player("player.csv", ios::app);
			if (!f_player) { cerr << "cannot open player.csv" << "\n"; return 0; }
			f_player << p.show_name() << ',' << p.show_EXP() << ',' << p.show_level() << ',' << p.show_pass_num() << "\n";
			cout << "sign up success" << "\n";
			return 1;
	}
	else if (tmppaper[0] == "2")
	{
		question_setter q(tmppaper[1]);

		bool user_exist = false;
		for (auto &iter : all_question_setter)
		{
			if (iter.show_name() == q.show_name())
			{
				user_exist = true;
			}
		}
		if (user_exist)
		{
			cout << "user is existed,please login" << "\n";
			return 2;
		}

		all_question_setter.push_back(q);

		fstream f_question_setter("question_setter.csv", ios::app);
		if (!f_question_setter) { cerr << "cannot open question_setter.csv" << "\n"; return 0; }
		f_question_setter << q.show_name() << ',' << q.show_EXP() << ',' << q.show_level() << ',' << q.show_word_num() << "\n";
		cout << "sign up success" << "\n";
		return 1;
	}
	else
	{
		cout << "not right type please choose p or q\n"; 
	}
	return 0;
}

int login(vector<string>& tmppaper)
{
	string name=tmppaper[1];
	
	cout << "login\n";

	if (tmppaper[0]=="1")
	{
		vector<player>::iterator cur_p = online_player.begin();
		while (cur_p != online_player.end())
		{
			if ((*cur_p).show_name() == name)
			{
				cout << "already login";
				return 3;
			}
			cur_p++;
		}

		 cur_p = all_player.begin();
			while (cur_p != all_player.end())
			{
				if ((*cur_p).show_name() == name)
				{
					user_player = cur_p;
					online_player.push_back(*user_player);

					return 1;
				}
				else
				{
					cur_p++;
				}
			}

			return 2;
		
	}
	else if (tmppaper[0] == "2")
			{
				vector<question_setter>::iterator cur_p = all_question_setter.begin();
				while (cur_p != all_question_setter.end())
				{
					if (cur_p->show_name() == name)
					{
						user_question_setter = cur_p;
						return 1;
					}
					else
					{
						cur_p++;
					}
				}
				return 2;
			}
		
}

int logout(vector<string>& tmppaper)
{
		string name = tmppaper[0];

		cout << "logout\n";

		vector<player>::iterator cur_p = online_player.begin();
		while (cur_p != online_player.end())
		{
			cout << (*cur_p).show_name()<<"\t*\t";
			if ((*cur_p).show_name() == name)
			{
				online_player.erase(cur_p);
				return 1;
			}
				cur_p++;
		}
		return 2;//not found


}

