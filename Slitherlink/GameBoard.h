#pragma once
#include "LoadQuestion.h"
#ifndef GAMEBOADR_H
#define GAMEBOARD_H
#define POINT_NUMBER 6
class GameBoard {
public:
	enum Direction {
		Up = 0,
		Left = 1,
		Down = 2,
		Right = 3,
	};
	enum ConnectState {
		Connect = 1,
		Disconnect = 2,
		NoChange = 0,
	};
	struct Point {
		int row;
		int column;
		Point* next;
	};
	GameBoard(LoadQuestion::Question ques);
	~GameBoard();
	void GameInit();
	void DrawGame();
	void CreateCheckMap();
	void SetConnect(int row, int column, Direction direction, ConnectState state);
	void Click();
	int CaculateRow(int y);
	int CaculateColumn(int x);
	int CaculateDirection(int x, int y);
	void test();
	bool CheckFit();
	int** connectMap;
	int size;
	bool finish(int x, int y);
	bool Reset(int x, int y);
	void DrawIndex();
	void ModeSelect();
	double Countdown(time_t start);
	static bool mode;
	bool finished = false;
	void HallofFame(vector<LoadQuestion::Tuple> tuples);
	void HallofFame();
	//���һ���������ֻ���
	void DrawFinish();
	//����ť
	void DrawButton(int x, int y, char text[]);
	//�������ֿ���
	void PlayMusic(bool on = true);
	static int difficulty ;
	// �޲ι���
	GameBoard();
	void AddQuestion(LoadQuestion::Question ques);
private:
	
	LoadQuestion::Question ques;
	int static challegeTime;

	int** numMap;
	int** checkMap;
	int startx = 100;
	int starty = 100;
	int resetPointX;
	bool musicIsOn = false;
	int** Clone(int** connectMap);
	bool find(Point* head, int i, int j);
	void insert(Point* head, Point* insert);
	void DrawMusicButton();
	bool PressMusicButton(int x, int y);
	bool CloseMusic(int x);
	static void DrawTime(time_t start);
	static bool stop;
	void DrawSetting();
	void GameSetting();
	// �����Ѷ�
	void UpdateDifficulty();
	// ������սʱ��
	void SetChallengeTime();
	// ��ҳ��� ������Ŀ��� ���������
	void DrawQuestion();
};



#endif

