#include <iostream>
using namespace std;
class DataAccess
{
public:
	DataAccess();
	~DataAccess();
	virtual void  Init(string userID);//初始化
	virtual string dataBaseConn(string username, string dataType);//连接数据库
	virtual string dataOper(string ID ,string SQLinfo);//数据增杀改操作
	virtual bool affairBegin(string ID);//事务初始化
	virtual bool affairCommit(string ID);//事务提交
	virtual bool affairRollBack(string ID);//事务回滚
	virtual bool affairEnd(string ID);//事务结束
	virtual string dataSearchByTxt(string ID,string SQLinfo , string savePath);//文本方式查询
	virtual string dataSearchByMemory(string ID,string SQLinfo);//内存方式查询
	virtual string lobSearch(string ID, string SQLinfo ,string savePath);//大字段数据查询
	virtual string lobInsert(string ID, string SQLinfo, string filePath);//大字段数据插入
	virtual string dataBaseDisconn(string ID);//数据库断开连接
	virtual string errinfo(string error_code);//获取出错信息
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