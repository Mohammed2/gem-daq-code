#ifndef _HelloTStore_h_
#define _HelloTStore_h_

#include "xdaq/Application.h"
#include "xdaq/WebApplication.h"
#include "xdata/Table.h"

class HelloTStore: public xdaq::Application  
{
 public:
  XDAQ_INSTANTIATOR();
        
  HelloTStore(xdaq::ApplicationStub * s) throw (xdaq::exception::Exception);
  void query(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
        
 private:
  xoap::MessageReference sendSOAPMessage(xoap::MessageReference &message) throw (xcept::Exception);
  std::string connect() throw (xcept::Exception);
  void disconnect(const std::string &connectionID) throw (xcept::Exception);
  void query(const std::string &connectionID,xdata::Table &results) throw (xcept::Exception);
  void insert(const std::string &connectionID,xdata::Table &newRows) throw (xcept::Exception);
  void getDefinition(const std::string &connectionID,xdata::Table &results) throw (xcept::Exception);
  void Default(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);

};

#endif
