#pragma once
#include"Header.h"
#include"Class.h"

constexpr auto ERR_CODE = 1;
constexpr auto WORD_IN = 2;
constexpr auto SIGN = 3;
constexpr auto LOGIN = 4;
constexpr auto P_UPDATE = 5;
constexpr auto Q_UPDATE = 6;
constexpr auto FIND = 7;
constexpr auto LOGOUT = 8;
/*ȫ�ֱ���*/


void getsockinfo();

//�ַ����ָ������s_database.cpp�У�
void string_split(std::string& s, std::vector<std::string>& v, const std::string& c);

extern vector<player> all_player;//player

extern vector<player> online_player;//

extern vector<player>::iterator user_player;//now player

extern vector<question_setter> all_question_setter;//question_setter

extern vector<question_setter>::iterator user_question_setter;//now question_setter

extern vector<string> word_v;//words

extern string username_player, username_question_setter;//now username

/*��ʼ����ȡinit.cpp*/
void read_words();

void read_player();

void read_question_setter();

/*ע��͵�¼*/
int sign_up(vector<string>& tmppaper);

int login(vector<string>& tmppaper);

int logout(vector<string>& tmppaper);

void getsockinfo();
/*��Ϸ��ʼ*/
int update_player(vector<string> tmpinfo);

/*����ʿ�*/
int update_question_setter(string name,vector<string> tmpinfo);

/*��ӡ��Ϣ*/
void print_player();

void print_question_setter();

/*����*/
void searchmode(vector<string>& tmpinfo);
