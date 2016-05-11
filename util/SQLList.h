#include<iostream>
#include<vector>
#include<sstream>
#include<map>
using namespace std;

#ifndef SQLLIST
#define SQLLIST

class SQLList {
public:
	vector<map<string,string> > sqlList;
	int currentSize;
	//map<string,string> test;
	SQLList();
	~SQLList();
	int size();
	map<string,string> get(int index);
	void push(map<string,string> mapparam);
}
;
#endif
