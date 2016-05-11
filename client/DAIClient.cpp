
#include "DAIClient.h"


DAIClient::DAIClient(){
	//Host = new string("localhost");
	//this->Host = "localhost";
	//this->Host = "192.168.213.235"; //�ĳɴ������ļ�UpNodeAddress.properties�ж�ȡ
	PropertyUtil::PropertyMapT pmt;
	PropertyUtil::read("UpNodeAddress.properties",pmt);
	cout<<"in DAIClient()"<<endl;
	this->Host = PropertyUtil::getPropery(pmt,"up_address");
	this->Thrift_PORT = 9000;
	socket = boost::shared_ptr<TSocket> ( new TSocket(Host, Thrift_PORT));
	transport = boost::shared_ptr<TTransport>(new TBufferedTransport(socket));
	protocol = boost::shared_ptr<TProtocol>(new TBinaryProtocol(transport));
	client  = new DataInterfaceForwardClient(protocol);


	//�����ͻ���thrift���������߳�
	//thread1 = new boost::thread(&startReceiveSub);
	//thread2 = new boost::thread(&stopReceiveSub);
	

	//����java��DAIClient�����´�����������޸ģ���֮��open�����빹�췽����ͻ
	transport->open();
	thread1 = new boost::thread(boost::bind(&DAIClient::startReceiveSub,this));
}

DAIClient::DAIClient(string ip){

	cout<<"in DAIClient(String)"<<endl;
	this->Host = ip;
	this->Thrift_PORT = 9000;
	socket = boost::shared_ptr<TSocket> ( new TSocket(Host, Thrift_PORT));
	transport = boost::shared_ptr<TTransport>(new TBufferedTransport(socket));
	protocol = boost::shared_ptr<TProtocol>(new TBinaryProtocol(transport));
	client  = new DataInterfaceForwardClient(protocol);


	//�����ͻ���thrift���������߳�
	//thread1 = new boost::thread(&startReceiveSub);
	//thread2 = new boost::thread(&stopReceiveSub);
	

	//����java��DAIClient�����´�����������޸ģ���֮��open�����빹�췽����ͻ
	transport->open();
	//thread1 = new boost::thread(boost::bind(&DAIClient::startReceiveSub,this));
}

DAIClient::~DAIClient(){
}

void DAIClient::open(){
	if(!transport->isOpen())
	transport->open();
	//if( NULL == thread1 )
	//thread1 = new boost::thread(boost::bind(&DAIClient::startReceiveSub,this));
	//thread1->join();
	boost::shared_ptr<boost::thread> threadtest(new boost::thread(boost::bind(&DAIClient::startReceiveSub,this)));

	cout<<"in DAIClient open"<<endl;
}
void DAIClient::close(){
	if(!transport->isOpen())
	transport->close();
	if(NULL == thread2)
	thread2 = new boost::thread(boost::bind(&DAIClient::stopReceiveSub,this));
	//thread2->join();
	cout<<"in DAIClient close"<<endl;
}

void DAIClient::startReceiveSub(){
	cout<<"in startReceiveSub"<<endl;
	this->Server_PORT = 9002;

	boost::shared_ptr<PushMessageImpl> handler(new PushMessageImpl());
	boost::shared_ptr<TProcessor> processor(new PushMessageProcessor(handler));
	boost::shared_ptr<TServerTransport> serverTransport(new TServerSocket(this->Server_PORT));
    boost::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
    boost::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());
	
	this->server = new TSimpleServer(processor, serverTransport, transportFactory, protocolFactory);
	cout<<"begin to start sever"<<endl;
	this->server->serve();
	
	/*
	TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
	cout<<"begin to start sever"<<endl;
    server.serve();
	*/
}

void DAIClient::stopReceiveSub(){
	if(NULL != this->server ){
		this->server->stop();
	}
}

bool DAIClient::isSubServerStart =  false;


void threadtest(int i){
	cout<<"in threadtest "<<i<<endl;
}
