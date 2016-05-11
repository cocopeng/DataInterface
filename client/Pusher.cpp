#include "Pusher.h"
#include <iostream>
using namespace std;

#include <boost/thread/thread.hpp>

Pusher * Pusher::pusher = NULL;

//Pusher::Pusher(){
//}

void Pusher::getSubscription(SubscriptionCallBack *callBack){
	this->callBack = callBack;
	cout<<" please wait "<<endl;
	while(lock){
		boost::this_thread::sleep(boost::posix_time::milliseconds(100));
	}
	callBack->receiveSubsription(result);
	lock = true;
}

void Pusher::getSubscription(){

	if(NULL == callBack){
		callBack->receiveSubsription(result);
		cout<<"call back over"<<endl;
	} else
		cout<<"no client anymore"<<endl;
}
