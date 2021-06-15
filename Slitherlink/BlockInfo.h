#pragma once
#include<vector>

class BlockInfo {
public:
	int row;
	int column;
	int num;
	//点的连接方向
	int PDirect = 0;
	//the mask of the directions that forbidden to connected
	int PForbidMask = 0;
	int Info = 0;
	int LineNo = 0;
	int numCnt = 0;
	int forbidCnt = 0;
	// 方向元素值
	int RightEig;
	int DownEig;
	int numMask;
	BlockInfo(int row, int column, int num = -1);
	BlockInfo();
	~BlockInfo();
	void SetNum(int n);
	std::vector<int> ExpertInfo();
	void RestoreInfo(std::vector<int> newInfo);
	bool equal(BlockInfo other);
private:

};