#include"Header.h"
#include"Things.h"




HANDLE hMutex;

vector<player> all_player;//player

vector<player> online_player;//online_player

vector<string> online_player_ip;//online_player_ip

vector<player>::iterator user_player;//now player

vector<question_setter> all_question_setter;//question_setter

vector<question_setter>::iterator user_question_setter;//now question_setter

vector<string> word_v;//words

string username_player, username_question_setter;//now username

//read
void read_words()
{
	fstream f_words("worddata.csv", ios::in);
	if (!f_words) 
		{ cerr << "cannot open worddata.csv" << "\n"; return; }
	f_words.seekg(0, fstream::beg);
	string word;
	while (!f_words.eof())
	{
		f_words >> word;
		word_v.push_back(word);
	}
}
void read_player()
{
	fstream infile("player.csv", ios::in);
	if (!infile) 
		{ cerr << "cannot open player.csv" << "\n"; return; }
	infile.seekg(0, fstream::beg);//将读写光标移到文件的开头

	string str;
	while (getline(infile, str))
	{
		string name, buf;
		int level, pass_num, EXP;
		stringstream ss(str);

		getline(ss, name, ',');
		ss >> EXP;
		getline(ss, buf, ',');
		ss >> level;
		getline(ss, buf, ',');
		ss >> pass_num;
		getline(ss, buf);

		player temp(name, EXP, level, pass_num);
		all_player.push_back(temp);
	}
}
void read_question_setter()
{
	fstream infile("question_setter.csv", ios::in);
	if (!infile) { cerr << "cannot open question_setter.csv" << "\n"; return; }
	infile.seekg(0, fstream::beg);

	string str;
	while (getline(infile, str))
	{
		int level, word_num, EXP;
		string name, buf;

		stringstream ss(str);

		getline(ss, name, ',');
		ss >> EXP;
		getline(ss, buf, ',');
		ss >> level;
		getline(ss, buf, ',');
		ss >> word_num;
		getline(ss, buf);

		question_setter temp(name, EXP, level, word_num);
		all_question_setter.push_back(temp);
	}
}
void string_split(std::string& s, std::vector<std::string>& v, const std::string& c)
{
	std::string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (std::string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}