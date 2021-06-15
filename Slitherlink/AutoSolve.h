#pragma once
#include<vector>
#include<map>
#include<set>
#include"GameBoard.h"
#include"BlockInfo.h"
#include"MapStatis.h"
using namespace std;
class AutoSolve {
public:

	int RIGHT = 1;
	int DOWN = 2;
	int LEFT = 4;
	int UP = 8;
	AutoSolve(int** map, int size);
	~AutoSolve();
	bool SetConnect(int row, int column, int direction, bool sure);
private:
	bool finish = false;
	int Actioncnt = 0;
	int UnfitNum = 0;
	int lineNoAcu = 1;
	// 日志记录
	vector<vector<int>> log;
	int row;
	int column;
	// row+2 * column+2 的数组
	vector<vector<BlockInfo>> map;
	// 地图元素值
	int EigValue = 0;
	int** rowMap;
	vector<int> deadEig;
	int PConCnt[16] = { 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4 };
	int unfitNum = 0;
	std::map<int, vector<BlockInfo>> lineNoList;
	std::map<int, vector<BlockInfo>> disLineNoList;
	set<int> ChangedPoints;
	MapStatis* sta;
	vector<int> fixFormMask;
	std::map<int, vector<int>> fixForm;
	bool MatchFixForm(int row, int column);
	bool Try(int deep);
	bool Solute();
	bool SetForbidden(int r, int c, int direct);
	void Rollback(int actionCnt = 0);
};

