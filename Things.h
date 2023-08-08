#pragma once
#include"Header.h"
#include"Class.h"

constexpr auto ERR_CODE = 1;
constexpr auto WORD_IN = 2;
constexpr auto SIGN = 3;
constexpr auto LOGIN = 4;
constexpr auto GAME = 5;
constexpr auto PROBLEM = 6;
constexpr auto FIND = 7;
constexpr auto LOGOUT = 8;

/*全局变量*/

extern string type;

extern vector<string> word_v;//words

extern vector<string> word_add;//new words to server

extern player now_player;

extern question_setter now_question_setter;

/*socket初始化读取init.cpp*/
int getsockv(int state, vector<string>& words, SOCKET clientSocket);
int getsockinfo(int state, string& myInfo, SOCKET clientSocket);
SOCKET socket_init(SOCKADDR_IN addrServ);
/*注册和登录*/
void sign_up(SOCKADDR_IN addrServ);

int login(SOCKADDR_IN addrServ);

void logout(SOCKADDR_IN addrServ);

/*游戏开始*/
int game_starto(SOCKADDR_IN addrServ);
void update_player(SOCKADDR_IN addrServ,int tmpEXP);

/*扩充词库*/
void new_words(SOCKADDR_IN addrServ);
void update_question_setter(SOCKADDR_IN addrServ);

/*打印信息*/
void print_player();

void print_question_setter();


/*查找*/
void search_player(SOCKADDR_IN addrServ);

void search_question_setter(SOCKADDR_IN addrServ);

void rank_player(SOCKADDR_IN addrServ);

void rank_question_setter(SOCKADDR_IN addrServ);