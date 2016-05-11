#include "../access/DataAccessInterface.h"
#include <iostream>

using namespace std;

void testDataOper(string ID,DataAccessInterface dai);
void testTransaction1(string ID,DataAccessInterface dai);
void testDataSearchByMemory(string ID,DataAccessInterface dai);
void testDataSearchByTxt(string ID,DataAccessInterface dai);
void testLobSearch(string ID,DataAccessInterface dai);
void testLobInsert(string ID,DataAccessInterface dai);

#define MAX_PATH 1024

/*int main(int argc, char* argv[])
{
	cout<<"enter in the main1"<<endl;

    DataAccessInterface dai;
    string ID = dai.dataBaseConn("t1","3","25");
    cout<<"connection ID = "<<ID<<endl;

	return 0;
}*/

void testDataOper(string ID,DataAccessInterface dai){
		string SQLinfo = "update zhikong set description='three' where zhikong_id = 1 ;";
		string dataOperRes ;
		dataOperRes = dai.dataOper(ID, SQLinfo);
		cout<<"dataOperRes = "<<dataOperRes<<endl;
	}
void testTransaction1(string ID,DataAccessInterface dai){
		dai.transactionBegin(ID);

		string SQLinfo1 = "update zhikong set description='first' where zhikong_id = 1 ;";
		dai.dataOper(ID, SQLinfo1);
		string SQLinfo2 = "update zhikong set description = 'second' where zhikong_id = 2 ;";
		dai.dataOper(ID, SQLinfo2);
		string SQLinfo3 = "update zhikong set description='first' where zhikong_id = 1 ;";
		dai.dataOper(ID, SQLinfo3);
		string SQLinfo4 = "update zhikong set description = 'second' where zhikong_id = 2 ;";
		dai.dataOper(ID, SQLinfo4);
		string SQLinfo5 = "update zhikong set description='second' where zhikong_id = 1 ;";
		dai.dataOper(ID, SQLinfo5);
		string SQLinfo6 = "update zhikong set description = 'first' where zhikong_id = 2 ;";
		dai.dataOper(ID, SQLinfo6);
		dai.transactionCommit(ID);

	}

void testDataSearchByMemory(string ID,DataAccessInterface dai){
		string SQLinfo = "SELECT information_id, description FROM  `information` WHERE kind = 0 ";
		SQLList sqlList;
		dai.dataSearchByMemory(ID, SQLinfo );
	}

void testDataSearchByTxt(string ID,DataAccessInterface dai){
		string SQLinfo = "SELECT information_id, description FROM  `information` WHERE kind = 0 ";
		string spaceMark =" ";

		char   buffer[MAX_PATH];
        getcwd(buffer, MAX_PATH);
		cout<<"The   current   directory   is:   "<<buffer<<endl;
		//string * savePath2 = new string(buffer);
		string savePath(buffer);
		dai.dataSearchByTxt(ID, SQLinfo, savePath, spaceMark);
	}

void testLobSearch(string ID,DataAccessInterface dai){

	    char   buffer[MAX_PATH];
        getcwd(buffer, MAX_PATH);
		cout<<"The   current   directory   is:   "<<buffer<<endl;
		string directoryPath(buffer);
		//string filePath = directoryPath +"\\receive\\image.jpg";
		string filePath = directoryPath +"/receive/image.jpg";

		string SQLinfo = "SELECT image FROM  `information`  WHERE information_id = 12 ; ";
//		String savaPath;
		cout<<"filePath = "<<filePath<<endl;
		dai.lobSearch(ID, SQLinfo, filePath);
	}

void testLobInsert(string ID,DataAccessInterface dai){
		string SQLinfo = "insert into information (description , data ,image)  values('mountain','extra data is null',?)";

		char   buffer[MAX_PATH];
        getcwd(buffer, MAX_PATH);
		cout<<"The   current   directory   is:   "<<buffer<<endl;
		string directoryPath(buffer);

		//string filePath =directoryPath+"\\send\\image1.jpg";
		string filePath =directoryPath+"/send/image0.jpg";
		cout<<"in testLobInsert filePath =  "<<filePath<<endl;
		dai.lobInsert(ID, SQLinfo, filePath);
	}
