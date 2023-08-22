#include "Header.h"
#include "Class.h"
#include "Things.h"

man::man()
{
	EXP = 0;
	level = 0;
}

man::man(const man& p1)
{
	name = p1.name;
	EXP = p1.EXP;
	level = p1.level;
}

man::man(const string& n1)
{
	name = n1;
	EXP = 0;
	level = 0;
}

man::~man()
{
}

bool man::operator==(man const& A)
{
	return A.name == name;
}

bool man::operator<(const man& p1)
{
	return this->name < p1.name;
}

man& man::operator=(const man& p1)
{
	if (this == &p1) return *this;

	name = p1.name;
	EXP = p1.EXP;
	level = p1.level;
	return *this;
}
void man::update_level()
{
	level = sqrt(EXP / 10);
}



player::player()
{
	name = "0";
	level = 0;
	EXP = 0;
	pass_num = 0;
}

player::player(const player& p1)
{
	name = p1.name;
	EXP = p1.EXP;
	level = p1.level;
	pass_num = p1.pass_num;
}

player::player(string s)
{
	name = s;
	EXP = 0;
	level = 0;
	pass_num = 0;
}

player::player(string n, int e, int l, int r)
{
	name = n;
	EXP = e;
	level = l;
	pass_num = r;
}

player::~player()
{
}

bool player::operator<(const player& p1)
{
	return this->name < p1.name;
}

player& player::operator=(const player& p1)
{
	if (this == &p1) return *this;

	name = p1.name;
	EXP = p1.EXP;
	level = p1.level;
	pass_num = p1.level;
	return *this;
}

void player::update_EXP(int difficulty)
{
	EXP = EXP + EXP_BASE * difficulty;
	cout << "EXP+" << EXP_BASE * difficulty << "\n";
}




question_setter::question_setter()
{
	name = "0";
	EXP = 0;
	level = 0;
	word_num = 0;
}

question_setter::question_setter(string s)
{
	name = s;
	EXP = 0;
	level = 0;
	word_num = 0;
}

question_setter::question_setter(string n,int e, int l, int w)
{
	name = n;
	EXP = e;
	level = l;
	word_num = w;
}

question_setter::~question_setter()
{
}

bool question_setter::operator<(const question_setter& p1)
{
	return this->name < p1.name;
}

question_setter& question_setter::operator=(const question_setter& p1)
{
	if (this == &p1) return *this;

	name = p1.name;
	EXP = p1.EXP;
	level = p1.level;
	word_num = p1.word_num;
	return *this;
}


void question_setter::update_EXP(string in_word)
{
	sort(word_v.begin(), word_v.end(), [](const string& a1, const string& a2) {return a1.size() < a2.size(); });
	vector<string>::iterator it, input_it;
	input_it = find(word_v.begin(), word_v.end(), in_word);

	//单词序号
	int seq = 0;
	for (it = word_v.begin(); it != input_it; it++)
		seq++;
	int size = word_v.size();

	//根据单词所在位置，三级难度，加不同经验
	if (seq < (size) / 3)//EXP1
	{
		this->EXP = this->EXP + EXP_BASE;
		cout << "EXP+" << EXP_BASE << "\n";
	}
	else if ((size) / 3 <= seq && seq < (size) * 2 / 3)
	{
		this->EXP = this->EXP + EXP_BASE * 2;
		cout << "EXP+" << EXP_BASE * 2 << "\n";
	}
	else if ((size) * 2 / 3 <= seq && seq < (size) * 3 / 3)
	{
		this->EXP = this->EXP + EXP_BASE * 3;
		cout << "EXP+" << EXP_BASE * 3 << "\n";
	}
	
}
