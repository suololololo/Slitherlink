//#include"BlockInfo.h"
//#include<cstdlib>
//#include<ctime>
//#define N 999
//extern std::vector<int> infoNum;
//BlockInfo::BlockInfo(int r, int c, int n = -1) {
//	row = r;
//	column = c;
//	num = n;
//	srand((int)time(0));
//	RightEig = ((int(0x7fffffff + (rand() % (N + 1) / (float)(N + 1)) * 0x7fffffff)) << 32) + int((rand() % (N + 1) / (float)(N + 1)) * 0xffffffff);
//	DownEig = ((int(0x7fffffff + (rand() % (N + 1) / (float)(N + 1)) * 0x7fffffff)) << 32) + int((rand() % (N + 1) / (float)(N + 1)) * 0xffffffff);
//	if (n < 0) {
//		numMask = 0xf;
//	}
//	else {
//		SetNum(num);
//	}
//}
//
//void BlockInfo::SetNum(int n) {
//	num = n;
//	if (n < 0) {
//		numMask = 0xf;
//	}
//	else {
//		numMask = 1 << num;
//		Info = infoNum[n];
//	}
//}
//
//std::vector<int> BlockInfo::ExpertInfo() {
//	std::vector<int> temp = { row,column,PDirect,PForbidMask,Info,numMask,LineNo,numCnt,forbidCnt };
//	return temp;
//}
//
//void BlockInfo::RestoreInfo(std::vector<int> newInfo) {
//	row = newInfo[0];
//	column = newInfo[1];
//	PDirect = newInfo[2];
//	PForbidMask = newInfo[3];
//	Info = newInfo[4];
//	numMask = newInfo[5];
//	LineNo = newInfo[6];
//	numCnt = newInfo[7];
//	forbidCnt = newInfo[8];
//
//
//}
//
//bool BlockInfo::equal(BlockInfo other) {
//	if (row == other.row && column == other.column && PDirect == other.PDirect && Info == other.Info && PForbidMask == other.PForbidMask &&
//		numMask == other.numMask && LineNo == other.LineNo && numCnt == other.numCnt && forbidCnt == other.forbidCnt && num == other.num) {
//		return true;
//	} 
//	return false;
//}