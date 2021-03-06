// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "DataInterfaceForward.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

class DataInterfaceForwardHandler : virtual public DataInterfaceForwardIf {
 public:
  DataInterfaceForwardHandler() {
    // Your initialization goes here
  }

  void dataBaseConn(std::map<std::string, std::string> & _return, const std::map<std::string, std::string> & mappara) {
    // Your implementation goes here
    printf("dataBaseConn\n");
  }

  void dataOper(std::map<std::string, std::string> & _return, const std::map<std::string, std::string> & mappara) {
    // Your implementation goes here
    printf("dataOper\n");
  }

  void transactionBegin(std::map<std::string, std::string> & _return, const std::map<std::string, std::string> & mappara) {
    // Your implementation goes here
    printf("transactionBegin\n");
  }

  void transactionCommit(std::map<std::string, std::string> & _return, const std::map<std::string, std::string> & mappara) {
    // Your implementation goes here
    printf("transactionCommit\n");
  }

  void transactionRollBack(std::map<std::string, std::string> & _return, const std::map<std::string, std::string> & mappara) {
    // Your implementation goes here
    printf("transactionRollBack\n");
  }

  void transactionEnd(std::map<std::string, std::string> & _return, const std::map<std::string, std::string> & mappara) {
    // Your implementation goes here
    printf("transactionEnd\n");
  }

  void dataSearchByTxt(std::map<std::string, std::string> & _return, const std::map<std::string, std::string> & mappara) {
    // Your implementation goes here
    printf("dataSearchByTxt\n");
  }

  void dataSearchByMemory(std::map<std::string, std::string> & _return, const std::map<std::string, std::string> & mappara) {
    // Your implementation goes here
    printf("dataSearchByMemory\n");
  }

  void lobSearch(std::string& _return, const std::map<std::string, std::string> & mappara) {
    // Your implementation goes here
    printf("lobSearch\n");
  }

  void lobInsert(std::map<std::string, std::string> & _return, const std::map<std::string, std::string> & mappara, const std::string& bytes) {
    // Your implementation goes here
    printf("lobInsert\n");
  }

  void dataBaseDisconn(std::map<std::string, std::string> & _return, const std::map<std::string, std::string> & mappara) {
    // Your implementation goes here
    printf("dataBaseDisconn\n");
  }

  void errInfo(std::map<std::string, std::string> & _return, const std::map<std::string, std::string> & mappara) {
    // Your implementation goes here
    printf("errInfo\n");
  }

  void subscriptionRequest(std::map<std::string, std::string> & _return, const std::map<std::string, std::string> & mappara) {
    // Your implementation goes here
    printf("subscriptionRequest\n");
  }

};
/*
int main(int argc, char **argv) {
  int port = 9090;
  shared_ptr<DataInterfaceForwardHandler> handler(new DataInterfaceForwardHandler());
  shared_ptr<TProcessor> processor(new DataInterfaceForwardProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}
*/
