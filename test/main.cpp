#include "../access/DataAccessInterface.h"
#include "../client/SubscriptionClientTest.h"
#include<iostream>
#include <boost/lexical_cast.hpp>

#include "TestClass.h"
using namespace std;
#define MAX_PATH 1024

void testsub();
void testBoostThread();
void testBoostThread2();

int main(int argc, char** argv)
{
	testsub();
	//testBoostThread();
	//testBoostThread2();

	using boost::lexical_cast;
	int aa = lexical_cast<int>("123");
	cout<<aa<<endl;

	return 0;
}

void testBoostThread(){
	SubscriptionClientTest clientTest;
	cout<<"before"<<endl;
	clientTest.start();
	cout<<"after"<<endl;
}

void testBoostThread2(){
	TestClass testClass;
	cout<<"before"<<endl;
	testClass.start();
	cout<<"after"<<endl;
}

void testsub(){
    DataAccessInterface dai;
    dai.subscriptionRequest("RMV","test",0);
    dai.subscriptionRequest("ADD","test",0);

    SubscriptionClientTest clientTest;
   clientTest.getSubscription();

    string ID = dai.dataBaseConn("t1","3","25");
    cout<<"connection ID = "<<ID<<endl;

    dai.transactionBegin(ID);

    string SQLinfo2 = "update test set name = 'b' where id = 1 ;";
    dai.dataOper(ID, SQLinfo2);

    try{
            dai.transactionCommit(ID);
    }catch(exception e){
        dai.transactionRollBack(ID);
    }

    string disID = dai.dataBaseDisconn(ID);
    cout<<"disID = "<<disID<<endl;
}
