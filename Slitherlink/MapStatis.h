#pragma once
#include <vector>

// 2* 2 方块的信息值
class MapStatis {
public:
	std::vector<std::vector<std::vector<std::vector<int>>>> mapSta;
	MapStatis(int row, int column, std::vector<std::vector<BlockInfo>>* map);
	~MapStatis();
	void Refresh(int r, int c);
	void RefreshAll();
	void CaculateMask(int r, int c);
	void Updata(int r, int c);
	std::vector<std::vector<int>> decode(int mask);
private:
	int row;
	int column;
	// block 数
	int rowE;
	int columnE;
	std::vector<std::vector<BlockInfo>>* map;

};