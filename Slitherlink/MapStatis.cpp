//#include "MapStatis.h"
//#include "BlockInfo.h"
//using namespace std;
//MapStatis::MapStatis(int r, int c, vector<vector<BlockInfo>>* m) {
//	row = r;
//	column = c;
//	rowE = r + 2;
//	columnE = c + 2;
//	map = m;
//	// 4 维数组  初始化信息值，  
//	for (int i = 0; i < rowE; i++) {
//		vector<vector<vector<int>>> oneRow;
//		for (int j = 0; j < columnE; j++) {
//			vector<int> staInfoLast = { 0,0,0,0,0 };
//			vector<int> staInfoNew = { 0,0,0,0,0 };
//			vector<int> staInfoSqu = { 0,0,0,0,0 };
//			vector<vector<int>> temp{ staInfoLast, staInfoNew, staInfoSqu };
//			oneRow.push_back(temp);
//		}
//		mapSta.push_back(oneRow);
//	}
//}
//// 根据图上的数字计算信息值 具体为什么要这么计算 凭感觉
//void MapStatis::RefreshAll() {
//	for (int r = 0; r < rowE; r++) {
//		for (int c = 0; c < columnE; c++) {
//			BlockInfo block = (*map)[r][c];
//			int lastInfo = mapSta[r][c][0][1];
//			vector<int> staInfoNew{ block.numMask,block.Info , block.PDirect , block.PForbidMask,block.Info - lastInfo };
//			mapSta[r][c][1] = staInfoNew;
//		}
//	}
//	for (int r = 1; r < row; r++) {
//		for (int c = 1; c < column; c++) {
//			CaculateMask(r, c);
//		}
//	}
//
//}
//// 刷新某个点的信息值
//void MapStatis::Refresh(int r, int c) {
//	BlockInfo block = (*map)[r][c];
//	int lastInfo = mapSta[r][c][0][1];
//	vector<int> staInfoNew{ block.numMask,block.Info , block.PDirect , block.PForbidMask,block.Info - lastInfo };
//	mapSta[r][c][1] = staInfoNew;
//}
//// 掩码计算
//void MapStatis::CaculateMask(int r, int c) {
//	vector<vector<int>>& stainfo = (mapSta[r][c]);
//	if (r < 1 || r >= row || c < 1 || c >= column) {
//		stainfo[2][0] = stainfo[1][0] << 12;
//		stainfo[2][1] = stainfo[1][1];
//		stainfo[2][2] = stainfo[1][2] << 32;
//		stainfo[2][3] = stainfo[1][3] << 32;
//		stainfo[2][4] = stainfo[1][4];
//	}
//	else {
//		int num22 = 0;
//		int	info22 = 0;
//		int	pd33 = 0;
//		int	pf33 = 0;
//		int	infoDelta22 = 0;
//
//		vector<int>& newinfo2 = mapSta[r][c + 1][1];
//		vector<int>& newinfo3 = mapSta[r + 1][c][1];
//		vector<int>& newinfo4 = mapSta[r + 1][c + 1][1];
//		vector<vector<int>> temp{ stainfo[1] ,newinfo2, newinfo3, newinfo4 };
//		for (int i = 0; i < 4; i++) {
//			vector<int>& infonew = temp[i];
//			num22 <<= 4;
//			num22 += infonew[0];
//			info22 += infonew[1];
//			infoDelta22 += infonew[4];
//		}
//		for (int i = r; i < r + 3; i++) {
//			for (int j = c; j < c + 3; j++) {
//				BlockInfo newinfos = (*map)[i][j];
//				pd33 <<= 4;
//				pd33 |= newinfos.PDirect;
//				pf33 <<= 4;
//				pf33 |= newinfos.PForbidMask;
//			}
//		}
//		stainfo[2][0] = num22;
//		stainfo[2][1] = info22;
//		stainfo[2][2] = pd33;
//		stainfo[2][3] = pf33;
//		stainfo[2][4] = infoDelta22;
//	}
//}
//
//void MapStatis::Updata(int r, int c) {
//	mapSta[r][c][0] = mapSta[r][c][1];
//	mapSta[r][c][1][4] = 0;
//	mapSta[r][c][2][4] = 0;
//}
//
//vector<vector<int>> MapStatis::decode(int mask) {
//	int r = 0;
//	int c = 0;
//	int d = 0;
//	int temp[9][4] = { {0,0,32,0xf},{0,1,28,0xb} ,{0,2,24,0xb},{1,0,20,7},{1,1,16,3},{1,2,12,3},{2,0,8,7},{2,1,4,3},{2,2,0,3} };
//	vector<vector<int>> result;
//	for (int i = 0; i < 9; i++) {
//		r = temp[i][0];
//		c = temp[i][1];
//		int sh = temp[i][2];
//		int m = temp[i][3];
//		d = (mask >> sh) & m;
//		vector<int> v{ r,c,d };
//		result.push_back(v);
//	}
//	return result;
//}