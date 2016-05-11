
#include "SQLList.h"

SQLList::SQLList(){
	currentSize = 0;
}
SQLList::~SQLList(){

}

int SQLList::size(){
	return sqlList.size();
}

map<string,string> SQLList::get(int size){
	if(size >=0 && size < sqlList.size()){
		return sqlList[size];
	} else
	{
		map<string,string> maps;
		return maps;
	}
	
}

void SQLList::push(map<string,string> mapparam){
	sqlList.insert(sqlList.begin()+currentSize, mapparam);
	currentSize++;
}
;
