/**
 * Autogenerated by Thrift Compiler (0.9.1)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef PushMessage_H
#define PushMessage_H

#include <thrift/TDispatchProcessor.h>
#include "PushMessage_types.h"



class PushMessageIf {
 public:
  virtual ~PushMessageIf() {}
  virtual void push(std::vector<std::string> & _return, const std::vector<std::string> & messages) = 0;
  virtual void registerCompleteNotify(std::map<std::string, std::string> & _return, const std::map<std::string, std::string> & mappara) = 0;
};

class PushMessageIfFactory {
 public:
  typedef PushMessageIf Handler;

  virtual ~PushMessageIfFactory() {}

  virtual PushMessageIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(PushMessageIf* /* handler */) = 0;
};

class PushMessageIfSingletonFactory : virtual public PushMessageIfFactory {
 public:
  PushMessageIfSingletonFactory(const boost::shared_ptr<PushMessageIf>& iface) : iface_(iface) {}
  virtual ~PushMessageIfSingletonFactory() {}

  virtual PushMessageIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(PushMessageIf* /* handler */) {}

 protected:
  boost::shared_ptr<PushMessageIf> iface_;
};

class PushMessageNull : virtual public PushMessageIf {
 public:
  virtual ~PushMessageNull() {}
  void push(std::vector<std::string> & /* _return */, const std::vector<std::string> & /* messages */) {
    return;
  }
  void registerCompleteNotify(std::map<std::string, std::string> & /* _return */, const std::map<std::string, std::string> & /* mappara */) {
    return;
  }
};

typedef struct _PushMessage_push_args__isset {
  _PushMessage_push_args__isset() : messages(false) {}
  bool messages;
} _PushMessage_push_args__isset;

class PushMessage_push_args {
 public:

  PushMessage_push_args() {
  }

  virtual ~PushMessage_push_args() throw() {}

  std::vector<std::string>  messages;

  _PushMessage_push_args__isset __isset;

  void __set_messages(const std::vector<std::string> & val) {
    messages = val;
  }

  bool operator == (const PushMessage_push_args & rhs) const
  {
    if (!(messages == rhs.messages))
      return false;
    return true;
  }
  bool operator != (const PushMessage_push_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const PushMessage_push_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class PushMessage_push_pargs {
 public:


  virtual ~PushMessage_push_pargs() throw() {}

  const std::vector<std::string> * messages;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _PushMessage_push_result__isset {
  _PushMessage_push_result__isset() : success(false) {}
  bool success;
} _PushMessage_push_result__isset;

class PushMessage_push_result {
 public:

  PushMessage_push_result() {
  }

  virtual ~PushMessage_push_result() throw() {}

  std::vector<std::string>  success;

  _PushMessage_push_result__isset __isset;

  void __set_success(const std::vector<std::string> & val) {
    success = val;
  }

  bool operator == (const PushMessage_push_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const PushMessage_push_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const PushMessage_push_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _PushMessage_push_presult__isset {
  _PushMessage_push_presult__isset() : success(false) {}
  bool success;
} _PushMessage_push_presult__isset;

class PushMessage_push_presult {
 public:


  virtual ~PushMessage_push_presult() throw() {}

  std::vector<std::string> * success;

  _PushMessage_push_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _PushMessage_registerCompleteNotify_args__isset {
  _PushMessage_registerCompleteNotify_args__isset() : mappara(false) {}
  bool mappara;
} _PushMessage_registerCompleteNotify_args__isset;

class PushMessage_registerCompleteNotify_args {
 public:

  PushMessage_registerCompleteNotify_args() {
  }

  virtual ~PushMessage_registerCompleteNotify_args() throw() {}

  std::map<std::string, std::string>  mappara;

  _PushMessage_registerCompleteNotify_args__isset __isset;

  void __set_mappara(const std::map<std::string, std::string> & val) {
    mappara = val;
  }

  bool operator == (const PushMessage_registerCompleteNotify_args & rhs) const
  {
    if (!(mappara == rhs.mappara))
      return false;
    return true;
  }
  bool operator != (const PushMessage_registerCompleteNotify_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const PushMessage_registerCompleteNotify_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class PushMessage_registerCompleteNotify_pargs {
 public:


  virtual ~PushMessage_registerCompleteNotify_pargs() throw() {}

  const std::map<std::string, std::string> * mappara;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _PushMessage_registerCompleteNotify_result__isset {
  _PushMessage_registerCompleteNotify_result__isset() : success(false) {}
  bool success;
} _PushMessage_registerCompleteNotify_result__isset;

class PushMessage_registerCompleteNotify_result {
 public:

  PushMessage_registerCompleteNotify_result() {
  }

  virtual ~PushMessage_registerCompleteNotify_result() throw() {}

  std::map<std::string, std::string>  success;

  _PushMessage_registerCompleteNotify_result__isset __isset;

  void __set_success(const std::map<std::string, std::string> & val) {
    success = val;
  }

  bool operator == (const PushMessage_registerCompleteNotify_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const PushMessage_registerCompleteNotify_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const PushMessage_registerCompleteNotify_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _PushMessage_registerCompleteNotify_presult__isset {
  _PushMessage_registerCompleteNotify_presult__isset() : success(false) {}
  bool success;
} _PushMessage_registerCompleteNotify_presult__isset;

class PushMessage_registerCompleteNotify_presult {
 public:


  virtual ~PushMessage_registerCompleteNotify_presult() throw() {}

  std::map<std::string, std::string> * success;

  _PushMessage_registerCompleteNotify_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class PushMessageClient : virtual public PushMessageIf {
 public:
  PushMessageClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) :
    piprot_(prot),
    poprot_(prot) {
    iprot_ = prot.get();
    oprot_ = prot.get();
  }
  PushMessageClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) :
    piprot_(iprot),
    poprot_(oprot) {
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void push(std::vector<std::string> & _return, const std::vector<std::string> & messages);
  void send_push(const std::vector<std::string> & messages);
  void recv_push(std::vector<std::string> & _return);
  void registerCompleteNotify(std::map<std::string, std::string> & _return, const std::map<std::string, std::string> & mappara);
  void send_registerCompleteNotify(const std::map<std::string, std::string> & mappara);
  void recv_registerCompleteNotify(std::map<std::string, std::string> & _return);
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class PushMessageProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  boost::shared_ptr<PushMessageIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (PushMessageProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_push(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_registerCompleteNotify(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  PushMessageProcessor(boost::shared_ptr<PushMessageIf> iface) :
    iface_(iface) {
    processMap_["push"] = &PushMessageProcessor::process_push;
    processMap_["registerCompleteNotify"] = &PushMessageProcessor::process_registerCompleteNotify;
  }

  virtual ~PushMessageProcessor() {}
};

class PushMessageProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  PushMessageProcessorFactory(const ::boost::shared_ptr< PushMessageIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::boost::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::boost::shared_ptr< PushMessageIfFactory > handlerFactory_;
};

class PushMessageMultiface : virtual public PushMessageIf {
 public:
  PushMessageMultiface(std::vector<boost::shared_ptr<PushMessageIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~PushMessageMultiface() {}
 protected:
  std::vector<boost::shared_ptr<PushMessageIf> > ifaces_;
  PushMessageMultiface() {}
  void add(boost::shared_ptr<PushMessageIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void push(std::vector<std::string> & _return, const std::vector<std::string> & messages) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->push(_return, messages);
    }
    ifaces_[i]->push(_return, messages);
    return;
  }

  void registerCompleteNotify(std::map<std::string, std::string> & _return, const std::map<std::string, std::string> & mappara) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->registerCompleteNotify(_return, mappara);
    }
    ifaces_[i]->registerCompleteNotify(_return, mappara);
    return;
  }

};



#endif
