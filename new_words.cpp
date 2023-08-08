#include"Header.h"
#include"Things.h"

int update_question_setter(string name, vector<string> wordAddList)
{
	unsigned int wordCount = 0;
	string new_word;
	vector<question_setter>::iterator Iter = all_question_setter.begin();
	for (; Iter != all_question_setter.end();)
	{
		if (Iter->show_name() == name)
		{

			user_question_setter = Iter;
			break;
		}
		else
			Iter++;
	}
	for (wordCount = 0; wordCount < wordAddList.size(); wordCount++)
	{
		new_word = wordAddList[wordCount];
		vector<string>::iterator insert_result;
		insert_result = find(word_v.begin(), word_v.end(), new_word);
		if (insert_result == word_v.end())
		{
			word_v.push_back(new_word);

			user_question_setter->inc_word_num();
			user_question_setter->update_EXP(new_word);
			user_question_setter->update_level();
			cout << "new word success：" << word_v.back() << "\n";

			fstream wordfile("worddata.csv", ios::app);
			if (!wordfile) { cerr << "cannot open worddata.csv" << "\n"; return 0; }
			wordfile << new_word << "\n";
		}
		else
		{
			cout << "the word has already existed\n";
		}
	}
	vector<question_setter>::iterator iter_q;
	fstream f_question_setter("question_setter.csv", ios::out);
	for (iter_q = all_question_setter.begin(); iter_q != all_question_setter.end(); iter_q++)
	{
		f_question_setter << iter_q->show_name() << ',' << iter_q->show_EXP() << ',' << iter_q->show_level() << ',' << iter_q->show_word_num() << "\n";
	}
	return 1;
}