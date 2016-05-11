#include <thrift/transport/TTransport.h>
#include <thrift/transport/TSocket.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/server/TSimpleServer.h>

#include <boost/thread/thread.hpp>

#include "PushMessageImpl.h"
#include "../util/CProperty.h"


#include "../gen-cpp/DataInterfaceForward.h"
#include "../gen-cpp/PushMessage.h"
#include <thrift/server/TSimpleServer.h>

#include <iostream>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace std;
using namespace apache::thrift::server;
using boost::shared_ptr;
using boost::thread;


#ifndef DAICLIENT
#define DAICLIENT


class DAIClient{
private:
	//const int Thrift_PORT = 9000;
	int Thrift_PORT ;
	//static const char[] Host = new char{"localhost"};
	string Host;
	boost::shared_ptr<TSocket>  socket;
	boost::shared_ptr<TTransport>  transport;
	boost::shared_ptr<TProtocol>  protocol;

	//�����û��ӿڶ�thrift��������һЩ����
	int Server_PORT;
	TSimpleServer * server;
	boost::thread * thread1;
	boost::thread * thread2;
	void startReceiveSub();
	void stopReceiveSub();

	//�ñ����ж�
	static bool isSubServerStart ;

public:
	DataInterfaceForwardClient * client;
	DAIClient();
	DAIClient(string ip); //ָ��ip��ʼ��DAIClient
	~DAIClient();
	void open();
	void close();
};


void threadtest(int i);
#endif // !DAICLIENT
//private DAIClient:: static const int Thrift_PORT = 9000;
