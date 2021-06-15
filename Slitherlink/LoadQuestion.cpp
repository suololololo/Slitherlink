#include<iostream>
#include<fstream>
#include"LoadQuestion.h"
#include<vector>
LoadQuestion::LoadQuestion() {

}
LoadQuestion::~LoadQuestion() {

}

LoadQuestion::Question LoadQuestion::Load(string file,int index) {
	Question question;
	ifstream in(file);
	int i = 0;
	if (!in.is_open()) {
		return question;
	}
	else {
		in.read(reinterpret_cast<char*>(&question), sizeof(question));
		while (!in.eof()) {
			if (i == index) {
				return question;
			}
			i++;
			in.read(reinterpret_cast<char*>(&question), sizeof(question));
		}
	}

	in.close();
	question.difficulty = -1;
	return question;
}

void LoadQuestion::Save(string file) {
	Question question;
	question.difficulty = 1;
	question.size = 2;

	for (int i = 0; i < question.size; i++) {
		for (int j = 0; j < question.size; j++) {
			question.field[i][j] = 1;
		}
 	}
	fstream output(file, ios::out | ios::binary);
	if (!output) {
		cout << "error open file";
		return;
	}
	output.write(reinterpret_cast<char*>(&question), sizeof(question));
	output.close();

}

void LoadQuestion::Save(string file, LoadQuestion::Question que) {
	fstream output(file, ios::out | ios::binary|ios::app);
	if (!output) {
		return;
	}
	output.write(reinterpret_cast<char*> (&que), sizeof(que));
	output.close();
}

vector<LoadQuestion::Tuple> LoadQuestion::HallofFame(char username[], double time) {
	ifstream input("HallofFame.txt");
	vector <Tuple> tupleList;
	Tuple tuple;
	//这里还有问题
	if (!input.is_open()) {
		return tupleList;
	}
	int j = 1;
	string line;
	while (getline(input, line)) {
		vector<string> result = LoadQuestion::split(line, " ");
		Tuple tuple;
		tuple.id = atoi(result[0].c_str());
		tuple.username = result[1];
		tuple.time = atof(result[2].c_str());
		tupleList.push_back(tuple);
		j++;
	}
	input.close();
	Tuple newInsertTuple;
	newInsertTuple.id = j;
	newInsertTuple.time = time;
	newInsertTuple.username = username;
	tupleList.push_back(newInsertTuple);
	vector<Tuple> sortedList = sort(tupleList);
	fstream output("HallofFame.txt", ios::out );
	if (!output.is_open()) {
		return tupleList;
	}
	for (int i = 0; i < sortedList.size(); i++) {
		output << sortedList[i].id << " " << sortedList[i].username << " " << sortedList[i].time<<endl;
	}
	output.close();
	return sortedList;
}

vector<LoadQuestion::Tuple> LoadQuestion::sort(vector<Tuple> tuples)
{
	for (int i = 1; i < tuples.size(); i++) {
		for (int j = i; j > 0; j--) {
			if (tuples[j].time < tuples[j - 1].time) {
				Tuple temp = tuples[j];
				tuples[j] = tuples[j - 1];
				tuples[j - 1] = temp;
			}
			else {
				break;
			}
		}
	}
	for (int i = 0; i < tuples.size(); i++) {
		tuples[i].id = i + 1;
	}
	return tuples;
}

vector<LoadQuestion::Tuple> LoadQuestion::HallofFame() {
	ifstream input("HallofFame.txt");
	vector<Tuple> tuples;

	//这里还有问题
	if (!input.is_open()) {
		return tuples;
	}
	string line;
	while (getline(input, line)) {
		vector<string> result = split(line, " ");
		Tuple tuple;
		tuple.id =atoi(result[0].c_str());
		tuple.username = result[1];
		tuple.time = atof(result[2].c_str());
		tuples.push_back(tuple);
	}
	input.close();
	return tuples;
}

vector<string> LoadQuestion::split(const string& src, string delimit, string null_subst )
{
	typedef basic_string<char>::size_type s_t;
	static const s_t npos = -1;
	if (src.empty() || delimit.empty())
	{
		throw "split:empty string\0";
	}
	vector<string> v;
	s_t deli_len = delimit.size();
	s_t index = npos, last_search_position = 0;
	while ((index = src.find(delimit, last_search_position)) != npos)
	{
		if (index == last_search_position)
		{
			v.push_back(null_subst);
		}
		else
		{
			v.push_back(src.substr(last_search_position, index
				- last_search_position));
		}
		last_search_position = index + deli_len;
	}
	string last_one = src.substr(last_search_position);
	v.push_back(last_one.empty() ? null_subst : last_one);
	return v;
}
