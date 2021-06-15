#include "FixForm.h"
#include<string>
#include<iostream>
#include<fstream>
using namespace std;

class Square {
public:
	int numSet[2][2];
	string name;
	vector<vector<vector<int>>> lineList;
	Square(FixForm* fixform) {
		int numMap[4];
		memcpy(numMap, fixform->numSet, sizeof(fixform->numSet) / sizeof(fixform->numSet[0]) * sizeof(int));
		numSet[0][0] = numMap[0];
		numSet[0][1] = numMap[1];
		numSet[1][0] = numMap[2];
		numSet[1][1] = numMap[3];
		for (int i = 0; i < 12; i++) {
			int ds = fixform->linesFlagList[i];
			if (ds == 0) {
				continue;
			}
			int ltmp[3][3] = { { 0, 0, 0},{0, 0, 0},{0, 0, 0} };
			ltmp[0][0] = (ds >> 11) | (((ds >> 5) & 1) << 8);
			ltmp[0][1] = ((ds >> 10) & 1) | (((ds >> 4) & 1) << 8);
			ltmp[0][2] = (((ds >> 3) & 1) << 8);
			ltmp[1][0] = ((ds >> 9) & 1) | (((ds >> 2) & 1) << 8);
			ltmp[1][1] = ((ds >> 8) & 1) | (((ds >> 1) & 1) << 8);
			ltmp[1][2] = (ds & 1) << 8;
			ltmp[2][0] = (ds >> 7) & 1;
			ltmp[2][1] = (ds >> 6) & 1;
			vector<int > temp1;
			temp1.push_back(ltmp[0][0]);
			temp1.push_back(ltmp[0][1]);
			temp1.push_back(ltmp[0][2]);
			vector<int> temp2;
			temp2.push_back(ltmp[1][0]);
			temp2.push_back(ltmp[1][1]);
			temp2.push_back(ltmp[1][2]);
			vector<int> temp3;
			temp2.push_back(ltmp[2][0]);
			temp2.push_back(ltmp[2][1]);
			temp2.push_back(ltmp[2][2]);
			vector<vector<int>> temp;
			temp.push_back(temp1);
			temp.push_back(temp2);
			temp.push_back(temp3);
			lineList.push_back(temp);
		}


	}
};
FixForm::FixForm(int numMap[4]) {
	for (int i = 0; i < 4; i++) {
		numSet[i] = numMap[i];
		numLines[i] = 0;

	}

	for (int i = 0; i < 9; i++) {
		points[i] = 0;
	}
	for (int i = 0; i < 12; i++) {
		lines[i] = 0;
		linesFlagList[i] = 0;
	}

}

FixForm::~FixForm() {

}

bool FixForm::UnconnectLine(int lineNumber) {
	if (lineNumber < 12 && lineNumber >= 0 && lines[lineNumber] == 1) {
		lines[lineNumber] = 0;
		for (int i = 0; i < 2; i++) {
			if (DSLine2Nums[lineNumber][i] != -1) {
				//对相邻数的周围边减1
				numLines[DSLine2Nums[lineNumber][i]]--;
			}
		}
		//给端点的连接数减1
		for (int i = 0; i < 4; i++) {
			points[DSLine2Points[lineNumber][i]]--;
		}
		return true;
	}
	else {
		return false;
	}
}

bool FixForm::ConnectLine(int lineNumber) {
	if (lineNumber < 12 && lineNumber >= 0 && lines[lineNumber] == 1) {
		lines[lineNumber] = 1;
		for (int i = 0; i < 2; i++) {
			if (DSLine2Nums[lineNumber][i] != -1) {
				numLines[DSLine2Nums[lineNumber][i]]++;
			}
		}
		for (int i = 0; i < 4; i++) {
			points[DSLine2Points[lineNumber][i]]++;
		}
		//检查连接合法性
		bool success = true;
		//检查一个数周围的连接是否超过该数
		for (int i = 0; i < 4; i++) {
			if (numLines[i] > numSet[i]) {
				success = false;
				break;
			}
		}

		if (success) {
			//检查一个端点的连接是否超过2
			for (int i = 0; i < 9; i++) {
				if (points[i] > 2) {
					success = false;
					break;
				}
			}
		}
		if (success) {
			//判断是否有环
			int startPoint = DSLine2Points[lineNumber][0];
			int nextPoint = DSLine2Points[lineNumber][1];
			//只有下一个点也是有两条连接才可能出现环
			if (points[startPoint] == 2 && points[nextPoint] == 2) {
				int currentLine = lineNumber;
				int nextLine = lineNumber;
				while (points[nextPoint] == 2) {
					for (int i = 0; i < 4; i++) {
						if (DSPoint2Lines[nextPoint][i] != -1) {
							// nextPoint 连接的边的编号 不是现在这条 且该边的连接数不为0 说明是另外一条
							if (DSPoint2Lines[nextPoint][i] != currentLine && lines[DSPoint2Lines[nextPoint][i]] != 0) {
								nextLine = DSPoint2Lines[nextPoint][i];
								break;
							}
						}

					}
					int point1 = DSLine2Points[nextLine][0];
					int point2 = DSLine2Points[nextLine][1];
					currentLine = nextLine;
					//下一端点
					nextPoint = point1 + point2 - nextPoint;
					if (nextPoint = startPoint) {
						success = false;
						break;
					}

				}
			}
		}
		if (!success) {
			UnconnectLine(lineNumber);
		}
		return success;
	}
	else {
		return false;
	}
}
// 检查最终连接状态， 数字周围的连接数必须等于数字，中心端点的连接数必须为0或2 ， 没有端点连接数超过2
bool FixForm::Check() {
	bool success = true;
	for (int i = 0; i < 4; i++) {
		if (numLines[i] != numSet[i]) {
			success = false;
			break;
		}
	}

	for (int i = 0; i < 9; i++) {
		if (points[i] > 2) {
			success = false;
			break;
		}
	}
	if (success && points[4] != 0 && points[4] != 2) {
		success = false;
	}
	//检查有没有环
	if (success) {
		int lineTemp[12];
		for (int i = 0; i < 12; i++) {
			lineTemp[i] = lines[i];
		}

		for (int i = 0; i < 12; i++) {
			if (lineTemp[i] == 1) {
				int currentLine = i;
				int nextLine = currentLine;
				int startPoint = DSLine2Points[i][0];
				int nextPoint = DSLine2Points[i][1];
				if (points[startPoint] == 2 && points[nextPoint] == 2) {
					while (points[nextPoint] == 2) {
						for (int i = 0; i < 4; i++) {
							if (DSPoint2Lines[nextPoint][i] != -1) {
								// nextPoint 连接的边的编号 不是现在这条 且该边的连接数不为0 说明是另外一条
								if (DSPoint2Lines[nextPoint][i] != currentLine && lines[DSPoint2Lines[nextPoint][i]] != 0) {
									nextLine = DSPoint2Lines[nextPoint][i];
									break;
								}
							}
						}
						int point1 = DSLine2Points[nextLine][0];
						int point2 = DSLine2Points[nextLine][1];
						lineTemp[currentLine] = 0;
						currentLine = nextLine;
						//下一端点
						nextPoint = point1 + point2 - nextPoint;
						if (nextPoint = startPoint) {
							success = false;
							break;
						}
					}
				}

			}
		}
	}

	if (success) {
		linesFlag = 0;
		for (int i = 0; i < 12; i++) {
			linesFlag <<= 1;
			if (i != 0) {
				linesFlag += 1;
			}
		}
		vector<int> linesFlagList2(12, 0);
		int i = 0;
		for (; i < 12; i++) {
			if (linesFlagList[i] == linesFlag || linesFlagList[i] == 0) {
				break;
			}
		}
		if (i < 12) {
			linesFlagList[i] = linesFlag;
		}

	}
	return success;

}

void FixForm::FillLine(int index) {
	int lineLeft = numSet[index] - numLines[index];

	int aroundLine[4];
	int lineFilled[4];
	for (int i = 0; i < 4; i++) {
		aroundLine[i] = DSNum2Lines[index][i];
		lineFilled[i] = 0;
	}
	for (int i = 0; i < 4; i++) {
		if (lines[aroundLine[i]] != 0) {
			lineFilled[i] = 1;
		}
	}
	if (lineLeft > 0) {
		int privot = 0;
		if (lineLeft == 4) {
			privot = 1;
		}
		else if (lineLeft == 2) {
			privot = 6;
		}
		else {
			privot = 4;
		}
		for (int i = 0; i < privot; i++) {
			bool success = true;
			for (int j = 0; j < 4; j++) {
				// 如果该线还未连接 ，  且枚举的情况中需要连接 尝试连接
				if (lineFilled[j] == 0 && Combinations[lineLeft][i][j] == 1) {
					success = ConnectLine(aroundLine[j]);
					if (!success) {
						break;
					}
				}
				// 如果该线已经连接 ，  且枚举的情况中需要连接尝试连接
				else if (lineFilled[j] != 0 && Combinations[lineLeft][i][j] == 1) {
					success = false;
					break;
				}
			}
			//成功连接下一条线
			if (success) {
				if (index != 3) {
					FillLine(index + 1);
				}
				else {
					Check();
				}
			}
			// 恢复状态
			for (int j = 0; j < 4; j++) {
				if (lineFilled[j] == 0 && lines[aroundLine[j]] != 0) {
					UnconnectLine(aroundLine[j]);
				}
			}
		}
	}
}

//void AllFixForm() {
//	vector<FixForm*> DSList;
//	for (int a = 0; a < 4; a++) {
//		for (int b = 0; b < 4; b++) {
//			for (int c = 0; c < 4; c++) {
//				for (int d = 0; d < 4; d++) {
//					int numMap[4] = { a,b,c,d };
//					FixForm* fixform = new FixForm(numMap);
//					DSList.push_back(fixform);
//				}
//			}
//		}
//	}
//	vector<Square*> squareList;
//	for (int i = 0; i < DSList.size(); i++) {
//		DSList[i]->FillLine(0);
//		Square* temp = new Square(DSList[i]);
//		squareList.push_back(temp);
//	}
//
//	fstream output("fixform.txt", ios::out | ios::app);
//	output << "DSList={" << endl;
//	for (int i = 0; i < squareList.size(); i++) {
//		if (squareList[i]->lineList.size() > 0) {
//			output << "{{{" << squareList[i]->numSet[0][0] << "," << squareList[i]->numSet[0][1] << "},{" 
//				<< squareList[i]->numSet[1][0] <<","<< squareList[i]->numSet[1][1] <<"}},";
//			for(int i = 0; i < squareList[i]->lineList[])
//		}
//	}
//	output <<"}"
//
//}

