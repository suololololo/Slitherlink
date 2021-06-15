#include"GameBoard.h"
#include"LoadQuestion.h"
#include<graphics.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<stdio.h>
#include<mmsystem.h>
#include <iostream>
#include<fstream>
using namespace std;




int main() {
	/*LoadQuestion* loadQuestion = new LoadQuestion();
	LoadQuestion::Question  ques;
	ques.difficulty = 3;
	ques.size = 7;
	ques.field[0][2] = 2;
	ques.field[0][4] = 2;

	ques.field[0][5] = 1;
	ques.field[0][6] = 2;
	ques.field[1][1] = 3;
	ques.field[1][3] = 3;
	ques.field[1][4] = 3;
	ques.field[2][0] = 2;
	ques.field[2][3] = 1;
	ques.field[2][5] = 1;
	ques.field[2][6] = 2;
	ques.field[3][2] = 2;
	ques.field[3][3] = 3;
	ques.field[3][4] = 3;
	ques.field[4][1] = 2;
	ques.field[4][2] = 1;
	ques.field[4][5] = 3;
	ques.field[5][0] = 3;
	ques.field[5][1] = 3;
	ques.field[5][3] = 3;
	ques.field[5][5] = 1;
	ques.field[6][4] = 3;
	loadQuestion ->Save("data.txt", ques);*/
	LoadQuestion* loadQuestion = new LoadQuestion();
	int i = 0;
	char username[30] = " ";
	cout << "请输入游戏者的名字";
	cin >> username;
	GameBoard* gameboard = new GameBoard();
	gameboard->PlayMusic(true);
	initgraph(640, 640);
	gameboard->DrawIndex();
	
	LoadQuestion::Question list = loadQuestion->Load("data.txt", i);
	if (list.difficulty == -1 || list.difficulty == 0) {
		return 1;
	}

	while (true) {
		while (list.difficulty != gameboard->difficulty) {
			i++;
			list = loadQuestion->Load("data.txt", i);
		}

		gameboard = new GameBoard(list);
		if (gameboard->mode) {
			gameboard->GameInit();
			gameboard->DrawGame();
			gameboard->Click();
			if (gameboard->finished) {
				i++;
				gameboard->DrawFinish();
			}
		}
		else {
			time_t start = time(NULL);
			gameboard->GameInit();
			gameboard->DrawGame();
			gameboard->Click();
			if (gameboard->finished) {
				i++;
				vector<LoadQuestion::Tuple> tuples = loadQuestion->HallofFame(username, gameboard->Countdown(start));
				gameboard->DrawFinish();
			}
		}

		list = loadQuestion->Load("data.txt", i);


	}

	gameboard->~GameBoard();


	return 0;
}
