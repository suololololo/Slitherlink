#pragma once
#include<vector>
#ifndef FIXFORM_H
#define FIXFORM_H
using namespace std;
class FixForm {
public:
	// 2*2 �����е��� ���к���
	int numSet[4] ;
	//ÿ�����ܹ��ı���
	int numLines[4];
	// ÿ���������״̬ ������ 1����  2 ����
	int points[9];
	//ÿ���ߵ�����״̬
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
	//-1 ��ʾ��Ч����
	//ÿ��������Χ�ߵı�� ˳ʱ��
	int	DSNum2Lines[4][4] = { {0, 7, 2, 6},{1, 8, 3, 7},{2, 10, 4, 9},{3, 11, 5, 10} };
	//ÿ�������ڱ���  -1 �������
	int DSLine2Nums[12][2] = { {0,-1},{1,-1},{0, 2},{1, 3},{2,-1},{3,-1},{0,-1},{0, 1},{1,-1},{2,-1},{2, 3},{3,-1} };
	// ÿ��������Χ�Ķ�����˳ʱ��
	int	DSNum2Points[4][4] = { {0, 1, 4, 3},{1, 2, 5, 4},{3, 4, 7, 6},{4, 5, 8, 7} };
	//ÿ���������ıߵı��
	int	DSPoint2Lines[9][4] = { {0, 6,-1,-1},{0, 1, 7,-1},{1, 8,-1,-1},{6, 2, 9,-1},{2, 7, 3, 10},{3, 8, 11,-1},{9, 4,-1,-1},{4, 10, 5,-1},{5, 11,-1,-1} };
	//ÿ���ߵ������˵� ���
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