#pragma once
#include<vector>
#ifndef FIXFORM_H
#define FIXFORM_H
using namespace std;
class FixForm {
public:
	// 2*2 格子中的数 先行后列
	int numSet[4] ;
	//每个数总共的边数
	int numLines[4];
	// 每个点的连接状态 无连接 1连接  2 连接
	int points[9];
	//每条边的连接状态
	int lines[12];
	int linesFlag = 0;
	int linesFlagList[12] = {-1};

	FixForm(int numMap[4]);
	~FixForm();
	bool UnconnectLine(int lineNum);
	bool ConnectLine(int lineNum);
	bool Check();
	void FillLine(int index);
	int** Combination(int m, int n);
private:
	//-1 表示无效数据
	//每个数字周围边的编号 顺时针
	int	DSNum2Lines[4][4] = { {0, 7, 2, 6},{1, 8, 3, 7},{2, 10, 4, 9},{3, 11, 5, 10} };
	//每个边相邻边数  -1 代表结束
	int DSLine2Nums[12][2] = { {0,-1},{1,-1},{0, 2},{1, 3},{2,-1},{3,-1},{0,-1},{0, 1},{1,-1},{2,-1},{2, 3},{3,-1} };
	// 每个数字周围的顶点编号顺时针
	int	DSNum2Points[4][4] = { {0, 1, 4, 3},{1, 2, 5, 4},{3, 4, 7, 6},{4, 5, 8, 7} };
	//每个点相连的边的编号
	int	DSPoint2Lines[9][4] = { {0, 6,-1,-1},{0, 1, 7,-1},{1, 8,-1,-1},{6, 2, 9,-1},{2, 7, 3, 10},{3, 8, 11,-1},{9, 4,-1,-1},{4, 10, 5,-1},{5, 11,-1,-1} };
	//每个边的两个端点 编号
	int	DSLine2Points[12][2] = { {0, 1},{1, 2},{3, 4},{4, 5},{6, 7},{7, 8},{0, 3},{1, 4},{2, 5},{3, 6},{4, 7},{5, 8} };
	int Combinations[4][6][4] = {
		{ {1, 0, 0, 0} ,{0, 1, 0, 0},{0, 0, 1, 0} ,{0, 0, 0, 1} },
		{ {1, 1, 0, 0},{1, 0, 1, 0},{1, 0, 0, 1},{0, 1, 1, 0},{0, 1, 0, 1},{0, 0, 1, 1} },
		{ {1, 1, 1, 0},{1, 1, 0, 1},{1, 0, 1, 1},{0, 1, 1, 1} },
		{ {1, 1, 1, 1} }
	};
	void AllFixForm();
};



#endif