#include <iostream>
using namespace std;
class DataAccess
{
public:
	DataAccess();
	~DataAccess();
	virtual void  Init(string userID);//��ʼ��
	virtual string dataBaseConn(string username, string dataType);//�������ݿ�
	virtual string dataOper(string ID ,string SQLinfo);//������ɱ�Ĳ���
	virtual bool affairBegin(string ID);//�����ʼ��
	virtual bool affairCommit(string ID);//�����ύ
	virtual bool affairRollBack(string ID);//����ع�
	virtual bool affairEnd(string ID);//�������
	virtual string dataSearchByTxt(string ID,string SQLinfo , string savePath);//�ı���ʽ��ѯ
	virtual string dataSearchByMemory(string ID,string SQLinfo);//�ڴ淽ʽ��ѯ
	virtual string lobSearch(string ID, string SQLinfo ,string savePath);//���ֶ����ݲ�ѯ
	virtual string lobInsert(string ID, string SQLinfo, string filePath);//���ֶ����ݲ���
	virtual string dataBaseDisconn(string ID);//���ݿ�Ͽ�����
	virtual string errinfo(string error_code);//��ȡ������Ϣ
};

DataAccess
::DataAccess
()
{
}

DataAccess
::~DataAccess
()
{
}