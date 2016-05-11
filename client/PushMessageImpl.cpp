#include "PushMessageImpl.h"
#include "Pusher.h"
#include<iostream>
using namespace std;
/*
PushMessageImpl::PushMessageImpl(){

}
*/
void PushMessageImpl:: push(std::vector<std::string> & _return, const std::vector<std::string> & messages){
	cout<<"in PushMessageImpl:: push print messages"<<endl;

	vector<std::string>::const_iterator it = messages.begin();
	while(it!=messages.end()){
		cout<<*it<<endl;
		it++;
	}

	/*
	for(auto iter = messages.begin() ; iter != messages.end() ;iter++){
		cout<<*iter<<endl;
	}
	*/

	Pusher* pusher = Pusher::getInstance();
	pusher->setResult(messages);
	pusher->setLock(false);
	_return.clear();
	copy(messages.begin(),messages.end(),_return.begin());
	
	cout<<"in PushMessageImpl:: push print _return"<<endl;

	vector<std::string>::iterator iter = _return.begin();

	for(; iter != _return.end() ;iter++){
		cout<<*iter<<endl;
	}

}
void PushMessageImpl:: registerCompleteNotify(std::map<std::string, std::string> & _return, const std::map<std::string, std::string> & mappara){
	printf("registerCompleteNotify\n");
}
