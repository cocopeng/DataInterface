#include"DataAccessInterface.h"



#include<fstream>
#include"json/json.h"
#include <string.h>

/*
#include <sys/types.h>
#include <sys/stat.h>
*/


typedef Json::Writer JsonWriter;  
typedef Json::Reader JsonReader;  
typedef Json::Value  JsonValue; 


class CommitException : public std::exception
{
public:
	CommitException(const std::string &s){cout<<s<<endl;}
    virtual ~CommitException() throw(){}
};


void print(JsonValue v)  
{  
    JsonValue::Members mem = v.getMemberNames();  
    for (Json::Value::Members::iterator iter = mem.begin(); iter != mem.end(); iter++)
    {  
        cout<<*iter<<"\t: ";  
        if (v[*iter].type() == Json::objectValue)  
        {  
            cout<<endl;  
            print(v[*iter]);  
        }  
        else if (v[*iter].type() == Json::arrayValue)  
        {  
            cout<<endl;  
            int cnt = v[*iter].size();
            for (int i = 0; i < cnt; i++)
            {  
                cout<<(v[*iter][i]);
            }  
        }  
        else if (v[*iter].type() == Json::stringValue)  
        {  
            cout<<v[*iter].asString()<<endl;  
        }  
        else if (v[*iter].type() == Json::realValue)  
        {  
            cout<<v[*iter].asDouble()<<endl;  
        }  
        else if (v[*iter].type() == Json::uintValue)  
        {  
            cout<<v[*iter].asUInt()<<endl;  
        }  
        else
        {  
            cout<<v[*iter].asInt()<<endl;  
        }  
    }  
    return;  
}


DataAccessInterface::DataAccessInterface()
{
	cout<<"in constructor DataAccessInterface"<<endl;
	//char tempIP[256];
	//cout<<"in constructor DataAccessInterface before localIP"<<endl;
	//this->localIP = getIP(tempIP);
	this->localIP = get_ip();
	cout<<"localIP="<<this->localIP<<endl;
	MapSerialzer::readFromFile(clientString);
	if(!clientString.empty()){
		cout<<"clientString is not null"<<endl;
		for(map<string,string>::iterator iter = clientString.begin(); iter != clientString.end(); iter++){
			cout<<iter->first<<" "<<iter->second<<endl;
			clientList.insert(pair<string,DAIClient>(iter->first,DAIClient(iter->second)));
		}
	}
	this->daiClient = new DAIClient();
}

DataAccessInterface::~DataAccessInterface()
{
	this->daiClient = NULL;
	delete this->daiClient;
}

DAIClient * DataAccessInterface::getClientByDataType(string dataType){
	map<string,DAIClient>::iterator  iter = clientList.find(dataType);
	if(iter != clientList.end()){
		return &(iter->second);
	} else 
		return NULL;

}

void DataAccessInterface::start(){

	daiClient->open();
}
void DataAccessInterface::end(){
	daiClient->close();
	if(this->tranStack.empty()){
		//throw exception("transaction end is not call");
		cout <<"transaction end is not call"<<endl;
	}
}

string DataAccessInterface::dataBaseConn(string username, string dataType,string dataBaseId)
{
	map<string,string> mapPara;
	string str_res;
	mapPara.insert(pair<string,string>("name",username));
	mapPara.insert(pair<string,string>("dataType",dataType));
	mapPara.insert(pair<string,string>("dataBaseId", dataBaseId));
	mapPara.insert(pair<string,string>("ip",this->localIP));
	placeTranIDAndOrder(mapPara);

	if(clientList.count(dataType)){
		this->daiClient = getClientByDataType(dataType);
	} else {
		cout<<"can't find the up access node by dataType"<<endl;
		cout<<"begin to use default UpNodeAddress "<<endl;
		//return "false";
	}

	

	cout<<"username = "<<username<<" dataType = "<<dataType<<endl;

	map<string,string> mapResult;  
	//daiClient.client->dataBaseConn(mapPara,mapResult);
	daiClient->client->dataBaseConn(mapResult,mapPara);
	cout<<"1 mapResult.size() = "<<mapResult.size()<<endl;
	for(map<string,string>::iterator iter = mapResult.begin();iter != mapResult.end();iter++){
		cout<<iter->first<<" "<<iter->second<<endl;
	}

	if(mapResult.count("redirectIpAddress")){
		this->remoteIP = getResultFromMap(mapResult,"redirectIpAddress");

		cout<<"get redirect IPAddress!"<<endl;
		cout<<"create a new DaiClient Proxy to IPAddress:"<<this->remoteIP<<endl;

		DAIClient dc(this->remoteIP);
		this->daiClient = &dc;

		this->clientList.insert(pair<string,DAIClient>(dataType,dc));
		this->clientString.insert(pair<string,string>(dataType,string(this->remoteIP)));

		//MapSerialzer::writeToFile(this->clientString);

		mapResult.clear();
		daiClient->client->dataBaseConn(mapResult,mapPara);

		if(mapResult.count("errorCode")){
			return this->getResultFromMap(mapResult,"errorCode");
		}
	} else {
		cout<<" no redirectIPAddress "<<endl;
	}

	cout<<"2 mapResult.size() = "<<mapResult.size()<<endl;
	str_res = getResultFromMap(mapResult,"id");

	if(str_res.length()!=0){
		cout<<"InterfaceName=dataBaseConn;LocalIP="<<this->localIP<<";RemoteIP="<<this->remoteIP<<";State=success;"<<endl;
	}else{
		cout<<"InterfaceName=dataBaseConn;LocalIP="<<this->localIP<<";RemoteIP="<<this->remoteIP<<";State=fail;"<<endl;
	}

	return str_res;
//	return "success";
}
string DataAccessInterface::dataOper(string ID ,string SQLinfo)
{
	map<string,string> mapPara;
	map<string,string> mapResult;  
	string str_res;
	mapPara.insert(pair<string,string>("id",ID));
	mapPara.insert(pair<string,string>("SQLinfo",SQLinfo));

	placeTranIDAndOrder(mapPara);
	daiClient->client->dataOper(mapResult,mapPara);
	
	str_res = getResultFromMap(mapResult,"res");
	cout<<"in dataoper res="<<str_res<<endl;
	if(str_res==string("0")){
		cout<<"InterfaceName=dataOper;LocalIP="<<this->localIP<<";RemoteIP="<<this->remoteIP<<";State=success;"<<endl;
	}else if(str_res==string("success")){
		cout<<"InterfaceName=dataOper;LocalIP="<<this->localIP<<";RemoteIP="<<this->remoteIP<<";State=success;"<<endl;
	}else{
		cout<<"InterfaceName=dataOper;LocalIP="<<this->localIP<<";RemoteIP="<<this->remoteIP<<";State=fail;"<<endl;
	}

	return str_res;
}
bool DataAccessInterface::transactionBegin(string ID)
{
	map<string,string> mapPara;
	map<string,string> mapResult;  
	string str_res;
	string transactionID;
	map<string,string>::iterator l_it;

	mapPara.insert(pair<string,string>("id",ID));
	placeTranIDAndOrder(mapPara);

	//cout<<"before transactionBegin"<<endl;
	daiClient->client->transactionBegin(mapResult,mapPara);
	//cout<<"after transactionBegin"<<endl;
	str_res = getResultFromMap(mapResult,"res");
	transactionID = getResultFromMap(mapResult, TransactionID);
	cout<<"transactionRes = "<<str_res<<" transactionID "<<transactionID<<endl;
	if(!transactionID.empty()){
		cout<<"transactionID is not null"<<endl;
		if(!tranStack.empty())
		{
			tranRelationMap.insert(pair<string,string>(transactionID,tranStack.top()));
		}
		tranStack.push(transactionID);
		tranOrderMap.insert(pair<string,int>(transactionID, 0));
	}else
		cout<<"transactionID is null"<<endl;

	if(str_res==string("success")){
		cout<<"InterfaceName=transactionBegin;LocalIP="<<this->localIP<<";RemoteIP="<<this->remoteIP<<";State=success;"<<endl;
		return true;
	}
	else{
		cout<<"InterfaceName=transactionBegin;LocalIP="<<this->localIP<<";RemoteIP="<<this->remoteIP<<";State=fail;"<<endl;
		return false;
	}
}
bool DataAccessInterface::transactionCommit(string ID)
{
	map<string,string> mapPara;
	map<string,string> mapResult;  
	string str_res;
	string transactionID;
	map<string,string>::iterator l_it;

	mapPara.insert(pair<string,string>("id",ID));
	placeTranIDAndOrder(mapPara);

	daiClient->client->transactionCommit(mapResult,mapPara);
	str_res = getResultFromMap(mapResult,"res");
	transactionID = tranStack.top();

	cout<<"in transactionCommit res="<<str_res<<endl;
	cout<<"in transactionCommit transactionID="<<transactionID<<endl;

	if(str_res==string("success")){
		tranRelationMap.erase(tranStack.top());
		tranOrderMap.erase(tranStack.top());
		tranStack.pop();
		cout<<"InterfaceName=transactionCommit;LocalIP="<<this->localIP<<";RemoteIP="<<this->remoteIP<<";State=success;"<<endl;
		return true;
	}else{
		cout<<"InterfaceName=transactionCommit;LocalIP="<<this->localIP<<";RemoteIP="<<this->remoteIP<<";State=fail;"<<endl;
		throw CommitException("transaction failed!");
	}
}
bool DataAccessInterface::transactionRollBack(string ID)
{
	map<string,string> mapPara;
	map<string,string> mapResult;  
	string str_res;
	string transactionID;
	map<string,string>::iterator l_it;

	mapPara.insert(pair<string,string>("id",ID));
	placeTranIDAndOrder(mapPara);


	daiClient->client->transactionRollBack(mapResult,mapPara);
	str_res = getResultFromMap(mapResult,"res");

	transactionID = tranStack.top();
	cout<<"in transactionRollBack transactionID="<<transactionID<<endl;

	tranRelationMap.erase(tranStack.top());
	tranOrderMap.erase(tranStack.top());
	tranStack.pop();

	if(str_res==string("true")){
		cout<<"InterfaceName=transactionRollBack;LocalIP="<<this->localIP<<";RemoteIP="<<this->remoteIP<<";State=success;"<<endl;
		return true;
	}else if(str_res==string("success")){
		cout<<"InterfaceName=transactionRollBack;LocalIP="<<this->localIP<<";RemoteIP="<<this->remoteIP<<";State=success;"<<endl;
		return true;
	}else{
		cout<<"InterfaceName=transactionRollBack;LocalIP="<<this->localIP<<";RemoteIP="<<this->remoteIP<<";State=fail;"<<endl;
		return false;
	}
}
bool DataAccessInterface::transactionEnd(string ID)
{
	return true;
}


string DataAccessInterface::dataSearchByTxt(string ID,string SQLinfo , string savePath, string spaceMark)
{
	map<string,string> mapPara;
	string str_res;
	string str_success;
	string transactionID;
	map<string,string>::iterator l_it;

	mapPara.insert(pair<string,string>("id",ID));
	mapPara.insert(pair<string,string>("SQLinfo",SQLinfo));
	mapPara.insert(pair<string,string>("savePath",savePath));
	mapPara.insert(pair<string,string>("spaceMark",spaceMark));

	placeTranIDAndOrder(mapPara);

	//��Ҫ���Ӵ洢
	map<string,string> mapResult;  

	daiClient->client->dataSearchByTxt(mapResult,mapPara);
	str_success = getResultFromMap(mapResult,"success");
	str_res = getResultFromMap(mapResult,"res");

	cout<<"success:"<<str_success<<endl;
	cout<<"str_res"<<str_res<<endl;
	//ifstream fin(savePath);
	ofstream fout;
	//fout.open((savePath+"/result.txt").c_str(),_Ios_Openmode::_S_trunc|_Ios_Openmode::_S_out);
	fout.open((savePath+"/result.txt").c_str(),ios::out|ios::trunc);
	//fout.open(savePath+"/result.txt",ios::out|ios::_Nocreate|ios::trunc);
	if(fout.is_open())
		fout<<str_res<<endl;
	fout.close();
	
	if(str_res == "1")
	{
		cout<<"InterfaceName=dataSearchByTxt;LocalIP="<<this->localIP<<";RemoteIP="<<this->remoteIP<<";State=fail;"<<endl;
		return "1";
	}
	else
	{
		cout<<"InterfaceName=dataSearchByTxt;LocalIP="<<this->localIP<<";RemoteIP="<<this->remoteIP<<";State=success;"<<endl;
		return "0";
	}
}

//string DataAccessInterface::dataSearchByMemory(string ID,string SQLinfo , SQLList & sqllist)
//{
//	map<string, string> mapPara;
//	mapPara.insert(pair<string, string>("id", ID));
//	mapPara.insert(pair<string, string>("SQLinfo", SQLinfo));
//
//	placeTranIDAndOrder(mapPara);
//	map<string, string> mapResult;
//
//	string str_res;
//
//	daiClient->client->dataSearchByMemory(mapResult,mapPara);
//	str_res = getResultFromMap(mapResult,"res");
//	cout<<"json str : "<<str_res<<endl;
//
//
//	// ++++
//	Json::Reader reader;
//	Json::Value root;
//
//	cout<<"before print root"<<endl;
//	print(root);
//	cout<<"after print root"<<endl;
//
//	Json::Value SelectResponseRarray;
//	map<string,string> resultMap;
//	if(reader.parse(str_res,root)){
//		//cout<<root["SelectResponse"]<<endl;
//		SelectResponseRarray = root["SelectResponse"];
//		//Json::ValueType type = SelectResponseRarray.type();
// 		if(SelectResponseRarray.isArray()){
//			for(unsigned int i = 0; i < SelectResponseRarray.size() ; i++) {
//				cout<<SelectResponseRarray[i]<<" ";
//			}
//			cout<<"print members end"<<endl;
//
//			//Json::Value::Members members = root.getMemberNames();
//
//			//Json::Value::iterator temp = SelectResponseRarray.begin();
//
//
//			cout<<"print members2"<<endl;
//
//			int k = 0;
//
//
//			Json::Value::Members members = SelectResponseRarray[k].getMemberNames();
//
//			cout<<"print members3"<<endl;
//
//			for(Json::Value::Members::iterator iter = members.begin();iter!=members.end();++iter)
//			{
//				cout<<(*iter)<<" "<<endl;
//			}
//			cout<<"after get root member"<<endl;
//			//for(Json::Value::Members::iterator iter = members.begin();iter!=members.end();++iter)
//			//{
//			//	cout<<(*iter)<<" "<<SelectResponseRarray[(*iter)]<<endl;
//			//	resultMap.insert(pair<string,string>(*iter,SelectResponseRarray[(*iter)].asString()));
//			//}
//			//sqllist.push(resultMap);
//			//for(int i = 0; i < SelectResponseRarray.size() ; i++){
//			//	Json::Value::Members member = SelectResponseRarray[i].getMemberNames();
//			//	SelectResponseRarray[i].;
//			//}
//		}
//		//ֻ�ǲ���
//		cout<<"sqllist.size() = "<<sqllist.size()<<endl;
//		for(int i = 0 ; i < sqllist.size() ; i++)
//		{
//			map<string,string>::iterator iter = sqllist.get(i).begin();
//			cout<<"key : "<<iter->first<<" second : "<<iter->second<<endl;
//		}
//	}
//
//	return str_res;
//}


string DataAccessInterface::dataSearchByMemory(string ID,string SQLinfo)
{
	map<string, string> mapPara;
	mapPara.insert(pair<string, string>("id", ID));
	mapPara.insert(pair<string, string>("SQLinfo", SQLinfo));

	placeTranIDAndOrder(mapPara);
	map<string, string> mapResult;

	string str_res;
	string str_succ;

	daiClient->client->dataSearchByMemory(mapResult,mapPara);
	str_res = getResultFromMap(mapResult,"res");
	str_succ = getResultFromMap(mapResult,"success");
	
	cout<<"in datasearchbymemory:res="<<str_succ<<endl;

	if(str_succ==string("0")){
		cout<<"InterfaceName=dataSearchByMemory;LocalIP="<<this->localIP<<";RemoteIP="<<this->remoteIP<<";State=success;"<<endl;
	}else{
		cout<<"InterfaceName=dataSearchByMemory;LocalIP="<<this->localIP<<";RemoteIP="<<this->remoteIP<<";State=fail;"<<endl;
	}

	return str_res;
}


string DataAccessInterface::lobSearch(string ID, string SQLinfo ,string savePath)
{
	map<string, string> mapPara;
	mapPara.insert(pair<string, string>("id", ID));
	mapPara.insert(pair<string, string>("SQLinfo", SQLinfo));
	mapPara.insert(pair<string, string>("savePath", savePath));

	placeTranIDAndOrder(mapPara);
	//+++
	string str_res;
	daiClient->client->lobSearch(str_res,mapPara);
	ofstream fout;
	//fout.open(savePath.c_str(),_Ios_Openmode::_S_trunc|_Ios_Openmode::_S_out);
	fout.open(savePath.c_str(),ios::trunc|ios::out);
	if(!fout.is_open())
		return NULL;
	//fout<<str_res<<endl;
	fout.write(str_res.data(),str_res.length());
	fout.close();

	if(str_res.length() != 0){
		cout<<"InterfaceName=lobSearch;LocalIP="<<this->localIP<<";RemoteIP="<<this->remoteIP<<";State=success;"<<endl;
		return "1";
	}
	else{
		cout<<"InterfaceName=lobSearch;LocalIP="<<this->localIP<<";RemoteIP="<<this->remoteIP<<";State=fail;"<<endl;
		return "0";
	}
}
/*
int _tmain(int argc, _TCHAR* argv[]){

	
	char   buffer[MAX_PATH];   
        _getcwd(buffer, MAX_PATH);   
		cout<<"The   current   directory   is:   "<<buffer<<endl;
		string directoryPath(buffer);

		string filePath =directoryPath+"\\send\\image1.jpg";
	ifstream fin;
	fin.open(filePath,ios::in|ios::_Nocreate|ios::binary);
	if(!fin.is_open())
		return NULL;

	int fileSize = getFileSize(filePath)+1;
	cout<<"in lobInsert fileSize = "<<fileSize<<endl;
	string test;
	char * szBuf = new char[fileSize]; //��ݻ���
	fin.read(szBuf,fileSize);
	fin.close();
	string filePath2 = directoryPath+"\\send\\image13.jpg";
	ofstream fout;
	fout.open(filePath2,ios::out|ios::_Nocreate|ios::binary);
	if(!fout.is_open())
		return NULL;
	fout.write(szBuf,fileSize);
	fout.close();
	//fin>>test;
	cout<<"test size() = "<<test.size()<<endl;
	char a;
	cin>>a;
	
	char   buffer[MAX_PATH];   
        _getcwd(buffer, MAX_PATH);   
		cout<<"The   current   directory   is:   "<<buffer<<endl;
		string directoryPath(buffer);
	string szDestFile= directoryPath+"\\send\\image12.jpg";
	string szOrigFile= directoryPath+"\\send\\image1.jpg";;
	copy_binary_file(szDestFile.c_str(),szOrigFile.c_str());
	int t;
	cin>>t;
	
}
*/

    bool copy_binary_file(const char * szDestFile, const char * szOrigFile)  
    {  
        if (szDestFile == NULL)  
        {  
            return false;  
        }  
      
        if (szOrigFile == NULL)  
        {  
            return false;  
        }  
      
        bool bRet = true;  
      
        std::ofstream fout(szDestFile, std::ios::binary | std::ios::app);  
        std::ifstream fin(szOrigFile, std::ios::binary);  
      
        if (fin.bad())  
        {  
            bRet = false;  
        }  
        else  
        {  
            while(!fin.eof())  
            {  
                char szBuf[256] = {0};  
                  
                fin.read(szBuf, sizeof(char) * 256);  
                  
                if (fout.bad())  
                {  
                    bRet = false;  
                    break;  
                }  
      
                //   
                fout.write(szBuf, sizeof(char) * 256);  
            }  
        }  
      
        fin.close();  
        fout.close();  
      
        return bRet;  
    }  


string DataAccessInterface::lobInsert(string ID, string SQLinfo, string filePath)
{
	map<string, string> mapPara;
	mapPara.insert(pair<string, string>("id", ID));
	mapPara.insert(pair<string, string>("SQLinfo", SQLinfo));
	mapPara.insert(pair<string, string>("filePath", filePath));

	placeTranIDAndOrder(mapPara);

	map<string, string> mapResult;
	//+++
	string str_res;
	ifstream fin;
	//fin.open(filePath.c_str(),_Ios_Openmode::_S_trunc|_Ios_Openmode::_S_out);
	fin.open(filePath.c_str(),ios::in);
	if(!fin.is_open())
		return NULL;
	/*
	int fileSize = getFileSize(filePath);
	cout<<"in lobInsert fileSize = "<<fileSize<<endl;
	int readBytes = 256;
	int seeksize = 0;
	char * szBuf = new char[fileSize]; //��ݻ���
	int a = 0;

	if(szBuf != NULL)
	{
		while(!fin.eof() && seeksize < fileSize)
		{
			a++;
			//fin.read(szBuf + readBytes, fileSize - readBytes);
			if(readBytes + seeksize > fileSize)
				fin.read(szBuf + seeksize, fileSize - seeksize);
			else
				fin.read(szBuf + seeksize, readBytes);
			if(fin.fail())
			{
				delete szBuf;
				break;
			}
			cout<<"after fin read fin.gcount() ="<<fin.gcount()<<endl;
			//readBytes += fin.gcount();
			seeksize += readBytes;
		}
	}

	//fin.clear();
	fin.read(szBuf,fileSize);
	fin.close();
	cout<<"a = "<<a<<"readBytes ="<<readBytes<<endl;
	cout<<"szBuf = "<<szBuf<<endl;
	*/
	//string str_SZ(szBuf);// = new string(szBuf);
	string str_SZ((std::istreambuf_iterator<char>(fin)),
                 std::istreambuf_iterator<char>());
	fin.close();

	cout<<"in lobInsert str_SZ.size() = "<<str_SZ.size()<<endl;
	daiClient->client->lobInsert(mapResult,mapPara,str_SZ);
	str_res = getResultFromMap(mapResult,"res");

	if(str_res.length()!=0){
		cout<<"InterfaceName=lobInsert;LocalIP="<<this->localIP<<";RemoteIP="<<this->remoteIP<<";State=success;"<<endl;
	}else{
		cout<<"InterfaceName=lobInsert;LocalIP="<<this->localIP<<";RemoteIP="<<this->remoteIP<<";State=fail;"<<endl;
	}

	return str_res;
}

//string DataAccessInterface::lobInsert(string ID, string SQLinfo, string filePath)
//{
//	map<string, string> mapPara;
//	mapPara.insert(pair<string, string>("id", ID));
//	mapPara.insert(pair<string, string>("SQLinfo", SQLinfo));
//	mapPara.insert(pair<string, string>("filePath", filePath));
//
//	placeTranIDAndOrder(mapPara);
//
//	map<string, string> mapResult;
//	//+++
//	string str_res;
//	ifstream fin;
//	//fin.open(filePath.c_str(),_Ios_Openmode::_S_trunc|_Ios_Openmode::_S_out);
//	fin.open(filePath.c_str(),ios::trunc|ios::out);
//	if(!fin.is_open())
//		return NULL;
//	/*
//	int fileSize = getFileSize(filePath);
//	cout<<"in lobInsert fileSize = "<<fileSize<<endl;
//	int readBytes = 256;
//	int seeksize = 0;
//	char * szBuf = new char[fileSize]; //��ݻ���
//	int a = 0;
//
//	if(szBuf != NULL)
//	{
//		while(!fin.eof() && seeksize < fileSize)
//		{
//			a++;
//			//fin.read(szBuf + readBytes, fileSize - readBytes);
//			if(readBytes + seeksize > fileSize)
//				fin.read(szBuf + seeksize, fileSize - seeksize);
//			else
//				fin.read(szBuf + seeksize, readBytes);
//			if(fin.fail())
//			{
//				delete szBuf;
//				break;
//			}
//			cout<<"after fin read fin.gcount() ="<<fin.gcount()<<endl;
//			//readBytes += fin.gcount();
//			seeksize += readBytes;
//		}
//	}
//
//	//fin.clear();
//	fin.read(szBuf,fileSize);
//	fin.close();
//	cout<<"a = "<<a<<"readBytes ="<<readBytes<<endl;
//	cout<<"szBuf = "<<szBuf<<endl;
//	*/
//	//string str_SZ(szBuf);// = new string(szBuf);
//	string str_SZ((std::istreambuf_iterator<char>(fin)),
//                 std::istreambuf_iterator<char>());
//	fin.close();
//
//	cout<<"in lobInsert str_SZ.size() = "<<str_SZ.size()<<endl;
//	daiClient->client->lobInsert(mapResult,mapPara,str_SZ);
//	str_res = getResultFromMap(mapResult,"res");
//	return str_res;
//}



string DataAccessInterface::dataBaseDisconn(string ID)
{
	map<string,string> mapPara;
	string str_res;
	mapPara.insert(pair<string,string>("id",ID));
	placeTranIDAndOrder(mapPara);

	map<string,string> mapResult; 
	daiClient->client->dataBaseDisconn(mapResult,mapPara);
	str_res = getResultFromMap(mapResult,"success");

	if(str_res==string("0")){
		cout<<"InterfaceName=dataBaseDisconn;LocalIP="<<this->localIP<<";RemoteIP="<<this->remoteIP<<";State=success;"<<endl;
	}else{
		cout<<"InterfaceName=dataBaseDisconn;LocalIP="<<this->localIP<<";RemoteIP="<<this->remoteIP<<";State=fail;"<<endl;
	}


	return str_res;
}
string DataAccessInterface::errinfo(string errorcode)
{
	map<string,string> mapPara;
	string str_res;
	mapPara.insert(pair<string,string>("errorCode",errorcode));
	placeTranIDAndOrder(mapPara);

	map<string,string> mapResult;  
	daiClient->client->dataBaseConn(mapResult,mapPara);
	str_res = getResultFromMap(mapResult,"res");
	return str_res;
}
string DataAccessInterface::subscriptionRequest(string Oper, string tableName ,int mode )
{
	map<string,string> mapPara;
	map<string,string> mapResult;  
	string str_res;
	//char tempIP[256];
	//char * ip = getIP(tempIP);
	char * ip =get_ip();
	string ipstr(ip);
	//char c[8];

	cout<<"old mode"<<mode<<endl;

	string m;
	if(mode==0){
		m="0";
	}else if(mode==1){
		m="1";
	}else if(mode==2){
		m="2";
	}else if(mode==3){
		m="3";
	}
	//cout<<"old mode="<<mode<<endl;

	//sprintf(c,"%05x",mode);

	//cout<<"mode = "<<c<<endl;
	//string content = ipstr+","+tableName+","+string(c);
	cout<<"mode="<<m<<endl;
	string content = ipstr+","+tableName+","+m;
	cout<<"content = "<<content<<endl;
	mapPara.insert(pair<string,string>("Content",content));
	mapPara.insert(pair<string,string>("Mode",Oper));
	daiClient->client->subscriptionRequest(mapResult , mapPara);
	str_res = getResultFromMap(mapResult,"res");
	cout<<"Subscribe : "+str_res<<endl;

	return str_res;
	//modify 0306
	//return "success";
}
void DataAccessInterface::placeTranIDAndOrder(map<string,string>& mapPara)
{
	if(!tranStack.empty())
	{
		mapPara.insert(pair<string,string>(TransactionID,tranStack.top()));

		int transactionOder_num = getTransactionOrderbyID(tranStack.top());
		std::stringstream ss;
		string str;
		ss<<transactionOder_num;
		ss>>str;
		mapPara.insert(pair<string,string>(TransactionOrder,str));
	}
}
int DataAccessInterface::getTransactionOrderbyID(string transactionID)
{
	if(tranOrderMap.count(transactionID) == 0)
	{
		tranOrderMap.insert(pair<string,int>(transactionID,0));
		return 0;
	}
	map<string,int>::iterator l_it;
	l_it = tranOrderMap.find(transactionID);
	int i = l_it->second;
	i++;
	//l_it->second = i;
	tranOrderMap.insert(pair<string,int>(transactionID,i));
	return i;
}
string DataAccessInterface::getResultFromMap(map<string,string>&mapResult,string key)
{
	map<string,string>::iterator l_it;
	l_it = mapResult.find(key);
	string value;
	if(l_it == mapResult.end())
	{
		cout<<"can't find key "+key<<endl;
		return "";
	} else {
		value = l_it->second;
		return value;
	}

}

/*
int get_filesize(const char *filename)
{
    struct stat f_stat;
    if (stat(filename, &f_stat) == -1)
    {
        return -1;
    }
    return f_stat.st_size;
}
*/

int getFileSize(string &sFileName)
{
	/*
    struct stat buf;
    int iRet = stat(sFileName.c_str(), &buf);
    if (iRet == -1)
        return NULL;
    return buf.st_size;
	*/
	long  size;
FILE *fp;

fp=fopen(sFileName.c_str(),"rb");
fseek(fp,0,SEEK_END);
size=ftell(fp);
fclose(fp);
return size;
}

