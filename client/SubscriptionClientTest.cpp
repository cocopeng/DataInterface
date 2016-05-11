#include "SubscriptionClientTest.h"
#include "DAIClient.h"
#include "../access/DataAccessInterface.h"

#include <boost/thread/thread.hpp>
#include<iostream>

using namespace std;
using boost::thread;

SubscriptionClientTest::SubscriptionClientTest(){
	pusher = Pusher::getInstance();
}

void SubscriptionClientTest::getSubscription(){
	cout<<"1 getsubscription"<<endl;
	thread thread1(boost::bind(&SubscriptionClientTest::registerToPusher,this));

	//boost::shared_ptr<boost::thread> threadtestSub(new boost::thread(boost::bind(&SubscriptionClientTest::registerToPusher,this)));

	cout<<"after thread"<<endl;
}

void SubscriptionClientTest::receiveSubsription(LS result){
	if(result.empty())
		return;
	cout<<" in SubscriptionClientTest::receiveSubsription print result"<<endl;
	for(LS::iterator iter = result.begin(); iter != result.end(); iter++){
		cout<<*iter<<" "<<endl;
	}
	cout<<endl;
}

void SubscriptionClientTest::registerToPusher(){
	cout<<"in registerToPusher"<<endl;
	pusher->getSubscription(this);
}

void SubscriptionClientTest::hello(){
	cout<<"hello world . I am a boost thread"<<endl;
}

void SubscriptionClientTest::start(){
	cout<<"enter start"<<endl;
	boost::function0<void> f = boost::bind(&SubscriptionClientTest::hello,this);
	boost::thread thrd(f);
	thrd.join();
	cout<<"end start"<<endl;
}


//int main(int argc, char** argv)
//{
//	DataAccessInterface dai;
//	dai.start();
//	dai.subscriptionRequest("RMV","test",0);
//	dai.subscriptionRequest("ADD","test",0);
//
//	SubscriptionClientTest clientTest;
//	clientTest.getSubscription();
//
//	string ID = dai.dataBaseConn("t1","3","25");
//	cout<<"connection ID = "<<ID<<endl;
//
//	dai.transactionBegin(ID);
//
//	string SQLinfo2 = "update test set name = 'basin' where id = 2 ;";
//	dai.dataOper(ID, SQLinfo2);
//
//	dai.transactionCommit(ID);
//
//	string disID = dai.dataBaseDisconn(ID);
//	cout<<"disID = "<<disID<<endl;
//	//DAIClient dai;
//	//char a;
//	//cin>>a;
//	//dai.end();
//	//system("pause");
//	return 0;
//
//}

void threadtestSub(int i){
	cout<<"in threadtestSub "<<i<<endl;
}
