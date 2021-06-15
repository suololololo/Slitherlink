//#include"AutoSolve.h"
//#include"GameBoard.h"
//#include<iostream>
//#include<fstream>
//
//#define INFO_LINE 1
//using namespace std;
//AutoSolve::AutoSolve(int** m, int size) {
//	row = size;
//	column = size;
//	//map = new int* [row + 2];
//	//for (int i = 0; i < row + 2; i++) {
//	//	map[i] = new int[column + 2];
//	//}
//	rowMap = m;
//	for (int i = 0; i < row + 2; i++) {
//		vector<BlockInfo> oneRow;
//		for (int j = 0; j < column + 2; i++) {
//			BlockInfo temp(i, j, -1);
//			oneRow.push_back(temp);
//		}
//		map[i] = oneRow;
//	}
//
//	sta = new MapStatis(row, column, &map);
//
//}
//AutoSolve::~AutoSolve() {
//
//}
//
//
//
//bool AutoSolve::SetConnect(int row, int column, int  direct, bool sure) {
//	if (finish) {
//		return true;
//	}
//	bool success = true;
//	bool directionInverse = false;
//	BlockInfo blockStart = map[row][column];
//	Actioncnt++;
//	int actionCnt = Actioncnt;
//	// 日志记录 action编号， 操作类型 1 代表连接 2 代表定式匹配， 操作行 和列   操作类型 1 代表连接
//	vector<int> tuple;
//	tuple.push_back(actionCnt);
//	tuple.push_back(1);
//	tuple.push_back(row);
//	tuple.push_back(column);
//	log.push_back(tuple);
//
//	vector<int> changepoints;
//	if (direct == LEFT) {
//		direct == RIGHT;
//		column--;
//		directionInverse = true;
//	}
//	else if (direct == UP) {
//		direct = DOWN;
//		row--;
//		directionInverse = true;
//	}
//	BlockInfo block1, block2, block3;
//	int neweigValue, antidirect;
//	if (direct == RIGHT) {
//		if (column > this->column) {
//			return true;
//		}
//		block1 = map[row][column];
//		changepoints.push_back(row * 256 + column);
//		block2 = map[row-1][column];
//		changepoints.push_back(row * 256 - 256 + column);
//		block3 = map[row][column + 1];
//		changepoints.push_back(row * 256 + column + 1);
//		neweigValue = EigValue ^ block1.RightEig;
//		antidirect = LEFT;
//	}
//	else if (direct == DOWN) {
//		if (row > this->row) {
//			return true;
//		}
//		block1 = map[row][column];
//		changepoints.push_back(row * 256 + column);
//		block2 = map[row - 1][column];
//		changepoints.push_back(row * 256 - 256 + column);
//		block3 = map[row][column + 1];
//		changepoints.push_back(row * 256 + column + 1);
//		neweigValue = EigValue ^ block1.DownEig;
//		antidirect = UP;
//	}
//	else {
//		std::cout << "set error";
//		return true;
//	}
//	//如果连接已经存在 1248 一个位表示一个方向
//	if (block1.PDirect & direct != 0) {
//		return true;
//	}
//	//如果连接已经被尝试过 且确定该链接无用
//	for (int i = 0; i < deadEig.size(); i++) {
//		if (neweigValue == deadEig[i]) {
//			return false;
//		}
//	}
//	BlockInfo blockEnd;
//	if (!directionInverse) {
//		blockEnd = block3;
//	}
//	else {
//		blockEnd = block1;
//	}
//	// 检查连接是否已经被禁止
//	if (block1.PForbidMask & direct != 0) {
//		if (!sure) {
//			deadEig.push_back(neweigValue);
//		}
//		return false;
//	}
//
//	//检查该点是否已经有两个连接
//	if (PConCnt[blockEnd.PDirect] >= 2 || PConCnt[blockStart.PDirect] >= 2) {
//		if (!sure) {
//			deadEig.push_back(neweigValue);
//		}
//		return false;
//	}
//	//检查边数是否已经大于数字
//	//边数
//	int unfit = unfitNum;
//	int num1 = block1.numCnt + 1;
//	// 没有限制的情况下是 -1 怎么解决
//	if (block1.num > 0) {
//		if (num1 > block1.num) {
//			if (!sure) {
//				deadEig.push_back(neweigValue);
//			}
//			return false;
//		}
//		else if (num1 == block1.num) {
//			unfit -= 1;
//		}
//	}
//	else if ((1 << num1) > block1.numMask) {
//		if (!sure) {
//			deadEig.push_back(neweigValue);
//		}
//		return false;
//	}
//
//	int num2 = block2.numCnt + 1;
//	if (block2.num > 0) {
//		if (num2 > block2.num) {
//			if (!sure) {
//				deadEig.push_back(neweigValue);
//			}
//			return false;
//		}
//		else if (num2 == block2.num) {
//			unfit -= 1;
//		}
//	}
//	else if ((1 << num2) > block2.numMask) {
//		if (!sure) {
//			deadEig.push_back(neweigValue);
//		}
//		return false;
//	}
//	// 检查是否已经产生圈
//	int lineNumber1 = blockStart.LineNo;
//	int lineNumber2 = blockEnd.LineNo;
//	if (lineNumber1 == lineNumber2 && lineNumber2 > 0) {
//		if (map.size() > 0) {
//			if (!sure) {
//				deadEig.push_back(neweigValue);
//			}
//			return false;
//		}
//		else if (unfit > 0) {
//			if (!sure) {
//				deadEig.push_back(neweigValue);
//			}
//			return false;
//		}
//	}
//
//	// 所有检查完成 开始连接
//	vector<int> infoStart = blockStart.ExpertInfo();
//	vector<int> infoEnd = blockEnd.ExpertInfo();
//	vector<int> infoNeighbor = block2.ExpertInfo();
//	int unfitsave = UnfitNum;
//	//连接
//	EigValue = neweigValue;
//	block1.PDirect |= direct;
//	block1.numCnt += 1;
//	if (block1.num < 0) {
//		block1.numMask &= 0x10 - (1 << block1.numCnt);
//	}
//	block1.Info += INFO_LINE;
//	block3.PDirect |= antidirect;
//	block2.numCnt += 1;
//	if (block2.num < 0) {
//		block2.numMask &= 0x10 - (1 << block2.numCnt);
//	}
//	block2.Info += INFO_LINE;
//	int lineNoSave, newLineNo, lineAction;
//	if (lineNumber1 == 0 && lineNumber2 == 0) {
//		blockEnd.LineNo = lineNoAcu;
//		blockStart.LineNo = lineNoAcu;
//		lineNoSave = lineNoAcu;
//		newLineNo = lineNoAcu;
//		// 创建新线
//		lineAction = 1;
//		lineNoAcu += 1;
//		vector<BlockInfo> temp{blockStart, blockEnd};
//		lineNoList.insert(make_pair(lineNoSave,temp));
//	}
//	// 扩展存在的线
//	else if (lineNumber1 > lineNumber2 && lineNumber2 == 0) {
//		newLineNo = lineNumber1;
//		lineNoSave = lineNumber1;
//		blockEnd.LineNo = lineNumber1;
//		lineAction = 2;
//		BlockInfo p1 = map[lineNoSave][0];
//		BlockInfo p2 = map[lineNoSave][1];
//		// 这个相等是怎么比较
//		if ( p1.equal(blockStart) ) {
//			vector<BlockInfo> temp{ blockEnd,p2 };
//			lineNoList.insert(make_pair(lineNoSave, temp));
//		}
//		else {
//			vector<BlockInfo> temp{ p1,blockEnd };
//			lineNoList.insert(make_pair(lineNoSave, temp));
//		}
//	}
//	else if (lineNumber2 > lineNumber1 && lineNumber1 == 0) {
//		newLineNo = lineNumber2;
//		lineNoSave = lineNumber2;
//		blockStart.LineNo = lineNumber2;
//		lineAction = 2;
//		BlockInfo p1 = map[lineNoSave][0];
//		BlockInfo p2 = map[lineNoSave][1];
//		if (p1.equal(blockEnd)) {
//			vector<BlockInfo> temp{ blockStart,p2 };
//			lineNoList.insert(make_pair(lineNoSave, temp));
//		}
//		else {
//			vector<BlockInfo> temp{ p1,blockStart };
//			lineNoList.insert(make_pair(lineNoSave, temp));
//		}
//	}
//	else if (lineNumber1 > lineNumber2 && lineNumber2  > 0) {
//		lineNoSave = lineNumber2;
//		newLineNo = lineNumber1;
//		lineAction = 3;
//		vector<BlockInfo> oldLine = lineNoList[lineNoSave];
//		lineNoList.erase(lineNoSave);
//		BlockInfo p1 = oldLine[0];
//		BlockInfo p2 = oldLine[1];
//		BlockInfo otherEnd;
//		if (p1.equal(blockEnd)) {
//			otherEnd = p2;
//		}
//		else {
//			otherEnd = p1;
//		}
//		p1 = lineNoList[newLineNo][0];
//		p2 = lineNoList[newLineNo][1];
//		if (p1.equal(blockStart)) {
//			vector<BlockInfo> temp{ otherEnd,p2 };
//			lineNoList.insert(make_pair(newLineNo, temp));
//		}
//		else {
//			vector<BlockInfo> temp{ p1,otherEnd };
//			lineNoList.insert(make_pair(newLineNo, temp));
//		}
//		otherEnd.LineNo = newLineNo;
//	}
//	// 游戏完成
//	else if (lineNumber1 == lineNumber2 && lineNumber2 > 0) {
//		lineNoSave = lineNumber1;
//		newLineNo = lineNumber1;
//		lineAction = 3;
//		vector<BlockInfo> oldLine = lineNoList[lineNoSave];
//		lineNoList.erase(lineNoSave);
//		finish = true;
//		return true;
//	}
//	for (int i = 0; i < changepoints.size(); i++) {
//		changepoints.push_back(changepoints[i]);
//	}
//
//
//
//}
//
//bool AutoSolve::Solute() {
//	bool successful = true;
//	// 匹配定式
//	for (int r = 0; r < row; r++) {
//		for (int c = 1; c < column; c++) {
//			successful = MatchFixForm(r, c);
//			if (!successful) {
//				break;
//			}
//		}
//		if (!successful) {
//			break;
//		}
//	}
//	// 深搜完成
//	if (successful) {
//		int deep = 1;
//		if (!finish) {
//			successful = Try(deep);
//		}
//	}
//
//	// 写日志
//	fstream output("log.txt", ios::out);
//	for (int i = 0; i < log.size(); i++) {
//		output << "{" << log[i][0] << "," << log[i][1] << "," << log[i][2] << "," << log[i][3] << "}" << endl;
//	}
//	output.close();
//}
//
//// 定时匹配
//bool AutoSolve::MatchFixForm(int r, int c) {
//	if (finish) {
//		return true;
//	}
//	// 写日志
//	vector<int> tempLog{ Actioncnt, 2,r,c };
//	log.push_back(tempLog);
//	if (r > row - 1) {
//		r = row - 1;
//	}
//	if (c > column - 1) {
//		c = column - 1;
//	}
//	int action = Actioncnt;
//	// 刷新图的信息值
//	sta->Refresh(r, c);
//	sta->Refresh(r, c + 1);
//	sta->Refresh(r + 1, c);
//	sta->Refresh(r + 1, c + 1);
//	sta->CaculateMask(r, c);
//	vector<int> temp = sta->mapSta[r][c][2];
//	int num22 = temp[0];
//	int info22 = temp[1];
//	int pd33 = temp[2];
//	int pf33 = temp[3];
//	int infoDelta = temp[4];
//	int matchcntall = 0;
//	int cvalue = 0xfffffffff;
//	int fvalue = 0;
//	for (int i = 0; i < fixFormMask.size(); i++) {
//		int numMask = fixFormMask[i];
//		// num22 包含 numMask
//		if (numMask & num22 == numMask) {
//			int matchcnt = 0;
//			vector<int> matchedv;
//			for (int j = 0; j < fixForm[numMask].size(); i++) {
//				int ffvalue = fixForm[numMask][j];
//				int cmask = (ffvalue | pd33) ^ ffvalue;
//				if (cmask != 0) {
//					continue;
//				}
//				cmask = ffvalue & pf33;
//				if (cmask != 0) {
//					continue;
//				}
//				matchcnt++;
//				matchcntall++;
//				matchedv.push_back(ffvalue);
//				cvalue &= ffvalue;
//				fvalue |= ffvalue;
//			}
//		}
//	}
//	// 没有定时匹配 说明有问题
//	if (matchcntall == 0) {
//		return false;
//	}
//	bool succ = true;
//	cvalue = (cvalue | pd33) ^ pd33;
//	if (cvalue != 0) {
//		vector<vector<int>> temp = sta->decode(cvalue);
//		for (int i = 0; i < temp.size(); i++) {
//			int roff = temp[i][0];
//			int coff = temp[i][1];
//			int ds = temp[i][2];
//			if (ds == 0) {
//				continue;
//			}
//			for (int i = 0; i < 4; i++) {
//				int direct = 1 << i;
//				if (succ && (direct & ds) != 0 && (direct & map[r + roff][c + coff].PDirect == 0)) {
//					succ = SetConnect(r + roff, c + coff, direct, true);
//				}
//			}
//			if (!succ) {
//				break;
//			}
//		}
//	}
//	fvalue ^= 0xfffffffff;
//	fvalue = (fvalue | pf33) ^ pf33;
//	if (succ && fvalue != 0) {
//		vector<vector<int>> temp = sta->decode(fvalue);
//		for (int i = 0; i < temp.size(); i++) {
//			int roff = temp[i][0];
//			int coff = temp[i][1];
//			int ds = temp[i][2];
//			if (ds == 0) {
//				continue;
//			}
//			for (int i = 0; i < 4; i++) {
//				int direct = 1 << i;
//				if (succ && (direct & ds) != 0 && (direct & map[r + roff][c + coff].PDirect == 0)) {
//					succ = SetForbidden(r + roff, c + coff, direct);
//				}
//			}
//			if (!succ) {
//				break;
//			}
//		}
//	}
//	sta->Updata(r, c);
//	return succ;
//
//}
//
//bool AutoSolve::SetForbidden(int r, int c, int direct) {
//
//}
//
//bool AutoSolve::Try(int deep) {
//	int eigvalueStart = EigValue;
//	int	actionCntStart = Actioncnt;
//	vector<int> temp{ Actioncnt, 3, deep };
//	log.push_back(temp);
//	while (ChangedPoints.size() > 0 && !finish) {
//		set<int> changedPoint = ChangedPoints;
//		ChangedPoints.clear();
//		std::map<int, vector<BlockInfo>>::iterator iter;
//		vector<BlockInfo> points;
//		set<int> dealed;
//		for ( iter= lineNoList.begin(); iter != lineNoList.end(); iter++) {
//			for (int i = 0; i < iter->second.size(); i++) {
//				points.push_back(iter->second[i]);
//			}
//		}
//		int dealcnt = 0;
//		for (int i = 0; i < points.size(); i++) {
//			if (finish) {
//				break;
//			}
//			int r = points[i].row;
//			int c = points[i].column;
//			int rc = r * 256 + c;
//			auto search = changedPoint.find(rc);
//			if (search != changedPoint.end()) {
//				changedPoint.erase(rc);
//				dealcnt++;
//				int off[8] = { -1,-1 ,-1,0,0,-1,0,0 };
//				for (int i = 0; i < 8; i+=2) {
//					int roff = off[i];
//					int coff = off[i + 1];
//					roff += r;
//					coff += c;
//					if (1 > roff) {
//						roff = 1;
//					}
//					if (1 > coff) {
//						coff = 1;
//					}
//					int rcoff = roff * 256 + coff;
//					auto searcha = dealed.find(rc);
//					if (searcha == dealed.end()) {
//						dealed.insert(rcoff);
//						if (!MatchFixForm(roff, coff)) {
//							deadEig.push_back(eigvalueStart);
//							Rollback(actionCntStart + 1);
//							return false;
//						}
//					}
//
//				}
//
//			}
//		}
//	}
//	if (!finish) {
//
//	}
//
//}