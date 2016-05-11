#include "MapSerializer.h"

string MapSerialzer::FILENAME;

int MapSerialzer::readFromFile(string filename ,map<string,string>& mappara){
	ifstream fin;  
    fin.open(filename.c_str());
    assert(fin.is_open()); 
	 Json::Reader reader;  
    Json::Value  root;  
    if (!reader.parse(fin, root, false))  
    {  
        return -1;  
    }  
	//cout<<"root is :"<<root<<endl;
	Json::Value::Members member;//Members ����vector<string>��typedef
	member = root.getMemberNames();

	//auto iter = member.begin()
	for (Json::Value::Members::iterator iter =  member.begin(); iter != member.end(); iter++) {
		//cout<<*iter<<" "<<root[*iter].asString()<<endl;
		mappara.insert(pair<string,string>(*iter,root[*iter].asString()));
	}
	fin.close();
	return 0;
}

int MapSerialzer::readFromFile(map<string,string>& mappara){
	cout<<"in MapSerialzer::readFromFile"<<endl;
	if(MapSerialzer::FILENAME.empty()){
		MapSerialzer::FILENAME = "serializedlist";
	}
	cout<<"MapSerialzer::FILENAME = "<<MapSerialzer::FILENAME<<endl;
	ifstream fin;  
    fin.open(MapSerialzer::FILENAME.c_str());
    assert(fin.is_open()); 
	 Json::Reader reader;  
    Json::Value  root;  
    if (!reader.parse(fin, root, false))  
    {  
    	cout<<"parse serializedlist failed "<<endl;
        return -1;  
    }  
	//cout<<"root is :"<<root<<endl;

	Json::Value::Members member;//Members ����vector<string>��typedef
	member = root.getMemberNames();
	for (Json::Value::Members::iterator iter = member.begin(); iter != member.end(); iter++) {
		cout<<*iter<<" "<<root[*iter].asString()<<endl;
		mappara.insert(pair<string,string>(*iter,root[*iter].asString()));
	}

	/*
	cout<<"begin print map "<<endl;
	for(auto iter2 = mappara.begin() ; iter2 != mappara.end(); iter2++){
		cout<<iter2->first<<" "<<iter2->second<<endl;
	}*/
	fin.close();
	return 0;
}

int MapSerialzer::writeToFile(string filename, map<string,string>& mappara){
	ofstream fout;  
    fout.open(filename.c_str());
    assert(fout.is_open());  
	fout.close();
	return 0;
}

int MapSerialzer::writeToFile(map<string,string>& mappara){
	if(MapSerialzer::FILENAME.empty()){
		MapSerialzer::FILENAME = "serializedlist";
	}
	ofstream fout;  
	//_Ios_Openmode::_S_trunc|_Ios_Openmode::_S_out
    fout.open(MapSerialzer::FILENAME.c_str(),ios::out|ios::ate);
    assert(fout.is_open());  
	Json::Value root; 
	for(map<string,string>::iterator iter2 = mappara.begin() ; iter2 != mappara.end(); iter2++){
		root[iter2->first] = iter2->second;
	}
	fout<<root<<endl;
	cout<<"finish write the file"<<endl;
	fout.close();
	return 0;
}

/*
int main()  
{
	MapSerialzer ms ;
	//PropertyUtil pu;
	map<string,string> mappara;
	MapSerialzer::readFromFile(mappara);

	cout<<"after analyse the file"<<endl;
	mappara.insert(pair<string,string>("3","192.168.1.1"));

	//MapSerialzer::writeToFile(mappara);

	int a;
	cin>>a;
}
*/
