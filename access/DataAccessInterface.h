//#include"DataAccess.h"

#include <stack>
#include <sstream>

#include <string>
#include <iostream>

#include<fstream>
#include"json/json.h"
using namespace std;

#include"../client/DAIClient.h"
#include"../util/SQLList.h"
#include "../util/MapSerializer.h"
#include "../util/IPGet.h"
//#define TransactionID "TransactionID";

const string TransactionID = "transactionID";
const string TransactionOrder = "transactionOrder";

class DataAccessInterface 
	//:public DataAccess
{
public:
	DataAccessInterface();
	~DataAccessInterface();

	string dataBaseConn(string username, string dataType, string dataBaseId);//������ݿ�
	string dataOper(string ID ,string SQLinfo);//�����ɱ�Ĳ���
	bool transactionBegin(string ID);//�����ʼ��
	bool transactionCommit(string ID);//�����ύ
	bool transactionRollBack(string ID);//����ع�
	bool transactionEnd(string ID);//�������
	string dataSearchByTxt(string ID,string SQLinfo , string savePath,string spaceMark);//�ı���ʽ��ѯ
	string dataSearchByMemory(string ID,string SQLinfo);//�ڴ淽ʽ��ѯ
	string lobSearch(string ID, string SQLinfo ,string savePath);//���ֶ���ݲ�ѯ
	string lobInsert(string ID, string SQLinfo, string filePath);//���ֶ���ݲ���
	string dataBaseDisconn(string ID);//��ݿ�Ͽ�����
	string errinfo(string errorcode);//��ȡ������Ϣ

	
	string  subscriptionRequest(string Oper, string tableName ,int mode);//���Ͷ�����Ϣ

	void start();
	void end();

private:
	DAIClient * daiClient;
	stack<string> tranStack;
	map<string,int> tranOrderMap;
	map<string,string> tranRelationMap;

	void placeTranIDAndOrder(map<string,string>& mapPara);
	int getTransactionOrderbyID(string transactionID);
	string getResultFromMap(map<string,string>&mapResult,string key);

	string remoteIP;
	map<string,DAIClient>  clientList;
	map<string,string>  clientString;
	string localIP;

	DAIClient * getClientByDataType(string ip);
};

int getFileSize(string &sFileName);
bool copy_binary_file(const char * szDestFile, const char * szOrigFile)  ;

