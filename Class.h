#pragma once
#include<string>
#define EXP_BASE 10 //最少可获得的经验值
using namespace std;

//基类
class man
{
public:
	man();
	man(const man& p1);
	man(const string& name1);
	~man();

	bool operator==(man const& A);
	bool operator<(const man& p1);

	man& operator=(const man& p1);

	string show_name() const { return name; }
	int show_level() const { return level; }
	int show_EXP() const { return EXP; }
	void update_level();


protected:
	string name;
	int level;
	int EXP;
};


//子类
class player :public man
{
public:
	player();
	player(const player& p1);
	player(string s);
	player(string n,  int e, int l, int r);//name EXP level rank
	~player();

	bool operator<(const player& p1);

	player& operator=(const player& p1);

	void inc_pass_num() { ++pass_num; }

	int show_pass_num()const { return pass_num; }

	void update_EXP(int difficulty);


private:
	int pass_num;//已闯过的关数
};


class question_setter :public man
{
public:
	question_setter();
	question_setter(string s);
	question_setter(string n, int e, int l, int w);
	~question_setter();

	bool operator<(const question_setter& p1);

	question_setter& operator=(const question_setter& p1);

	void inc_word_num() { ++word_num; };

	int show_word_num()const { return word_num; };

	void update_EXP(string word);

private:
	int word_num;//已写的题数
};

