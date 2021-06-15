#include<string>
#include<vector>
#ifndef LOADQUESTION_H
#define LOADQUESTION_H

using namespace std;
class LoadQuestion {
public :
	 struct  Question {
		int size;
		int difficulty;
		//int** field;
		int field[10][10] = { {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, 
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, 
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, 
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, 
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, 
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, 
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, 
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, 
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1} };
	};
	 struct Tuple {
		 int id;
		 string username = " ";
		 double time;
	 };

	LoadQuestion();
	~LoadQuestion();
	Question Load(string file,int index);
	void Save(string file);
	void Save(string file, Question que);
	vector<Tuple> HallofFame(char username[], double time);
	vector<Tuple> sort(vector<Tuple> tuples);
	static vector<Tuple> HallofFame();
	static vector<string> split(const string& src, string delimit, string null_subst = "");

};
#endif // !LOADQUESTION_H
