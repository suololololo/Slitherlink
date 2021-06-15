#include"Block.h"

#include <graphics.h>
Block::Block() {
	num = -1;
}

Block::~Block() {

}

void Block::SetNum() {
	char t[10];
	InputBox(t, 10, "ÊäÈëÊý×Ö");
	int ti = atoi(t);
	if(ti >= 0  && ti <= 3)
		num = ti;

}

int Block::GetNum() {
	return num;
}