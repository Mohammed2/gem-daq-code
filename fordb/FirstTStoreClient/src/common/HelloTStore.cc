#include "HelloTStore.h"
#include "TStoreRequest.h"
#include "toolbox/TimeInterval.h"
#include "tstore/client/AttachmentUtils.h"
#include "tstore/client/Client.h"
#include "xcept/tools.h"
#include "xgi/Utils.h"
#include "xgi/Method.h"
#include "xdaq/WebApplication.h"
#include "cgicc/HTMLClasses.h"
//#include "tstoretest/RandomData.h"

XDAQ_INSTANTIATOR_IMPL(HelloTStore)

HelloTStore::HelloTStore(xdaq::ApplicationStub * s) 
throw (xdaq::exception::Exception): xdaq::Application(s) 

{   
  xgi::bind(this,&HelloTStore::query, "query");
  //  xgi::bind(this,&HelloTStore::insert, "insert");
  xgi::bind(this,&HelloTStore::Default, "Default");

}

void HelloTStore::Default(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception) {
  //a link to the call query method below
  
  std::string method =
    toolbox::toString("/%s/query",getApplicationDescriptor()->getURN().c_str());

  
  *out << cgicc::HTMLDoctype(cgicc::HTMLDoctype::eStrict) << std::endl;
  *out << cgicc::html().set("lang", "en").set("dir","ltr") << std::endl;
  *out << cgicc::title("Simple Query") << std::endl;
  *out << cgicc::a("Query").set("href",method) << std::endl;
  //  *out << "<a href=\"query\">Query</a>" << std::endl;
  //  *out << "<a href=\"insert\">Insert</a>" << std::endl;
}

void HelloTStore::query(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception) {
  try {
    xdata::Table results;
		
    std::string connectionID=connect();
    query(connectionID,results);
    disconnect(connectionID);
		
    std::vector<std::string> columns=results.getColumns();
    for (unsigned long rowIndex=0;rowIndex<results.getRowCount();rowIndex++ ) {
      LOG4CPLUS_INFO(this->getApplicationLogger(),"\n");
      for (std::vector<std::string>::iterator column=columns.begin(); column!=columns.end(); ++column) {
	std::string value=results.getValueAt(rowIndex,*column)->toString();
	LOG4CPLUS_INFO(this->getApplicationLogger(),*column+": "+value);
      }
    }
  } catch (xcept::Exception &e) {
    LOG4CPLUS_ERROR(this->getApplicationLogger(),xcept::stdformat_exception_history(e));
  }
}

xoap::MessageReference HelloTStore::sendSOAPMessage(xoap::MessageReference &message) throw (xcept::Exception) {
  xoap::MessageReference reply;
	
  std::cout << "Message: " << std::endl;
  message->writeTo(std::cout);
  std::cout << std::endl;
	
  try {
    xdaq::ApplicationDescriptor * tstoreDescriptor = getApplicationContext()->getDefaultZone()->getApplicationDescriptor("tstore::TStore",0);
    xdaq::ApplicationDescriptor * tstoretestDescriptor=this->getApplicationDescriptor();
    reply = getApplicationContext()->postSOAP(message,*tstoretestDescriptor, *tstoreDescriptor);
  } 
  catch (xdaq::exception::Exception& e) {
    LOG4CPLUS_ERROR(this->getApplicationLogger(),xcept::stdformat_exception_history(e));
    XCEPT_RETHROW(xcept::Exception, "Could not post SOAP message. ", e);
  }
	
  xoap::SOAPBody body = reply->getSOAPPart().getEnvelope().getBody();
		
  std::cout << std::endl << "Response: " << std::endl;
  reply->writeTo(std::cout);
  std::cout << std::endl;
	
  if (body.hasFault()) {
    XCEPT_RAISE (xcept::Exception, body.getFault().getFaultString());
  }
  return reply;
}

std::string HelloTStore::connect() throw (xcept::Exception) {
  TStoreRequest request("connect");
	
  //add the view ID
  //  request.addTStoreParameter("id","urn:tstore-view-SQL:HelloTStore");
  request.addTStoreParameter("id","urn:tstore-view-SQL:HelloTStore");
	
  //this parameter is mandatory. "basic" is the only value allowed at the moment
  request.addTStoreParameter("authentication","basic");
	
  //login credentials in format username/password
  request.addTStoreParameter("credentials","castaned/Lederman12");
	
  //connection will time out after 10 minutes
  toolbox::TimeInterval timeout(600,0); 
  request.addTStoreParameter("timeout",timeout.toString("xs:duration"));
	
  xoap::MessageReference message=request.toSOAP();
	
  xoap::MessageReference response=sendSOAPMessage(message);
	
  //use the TStore client library to extract the response from the reply
  return tstoreclient::connectionID(response);
}

void HelloTStore::disconnect(const std::string &connectionID) throw (xcept::Exception) {
  TStoreRequest request("disconnect");
	
  //add the connection ID
  request.addTStoreParameter("connectionID",connectionID);
	
  xoap::MessageReference message=request.toSOAP();
	
  sendSOAPMessage(message);
}

void HelloTStore::query(const std::string &connectionID,xdata::Table &results) throw (xcept::Exception) {
  //for a query, we need to send some parameters which are specific to SQLView.
  //these use the namespace tstore-view-SQL. 
	
  //In general, you might have the view name in a variable, so you won't know the view class. In this
  //case you can find out the view class using the TStore client library:
  std::string viewClass=tstoreclient::classNameForView("urn:tstore-view-SQL:HelloTStore");
	
  //If we give the name of the view class when constructing the TStoreRequest, 
  //it will automatically use that namespace for
  //any view specific parameters we add.
  TStoreRequest request("query",viewClass);
	
  //add the connection ID
  request.addTStoreParameter("connectionID",connectionID);
	
  //for an SQLView, the name parameter refers to the name of a query section in the configuration
  //We'll use the "hello" one.
  request.addViewSpecificParameter("name","hello");
  
  xoap::MessageReference message=request.toSOAP();
  xoap::MessageReference response=sendSOAPMessage(message);
	
  //use the TStore client library to extract the first attachment of type "table"
  //from the SOAP response
  if (!tstoreclient::getFirstAttachmentOfType(response,results)) {
    XCEPT_RAISE (xcept::Exception, "Server returned no data");
  }
}


// void insert(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception) {
//   try {
//     xdata::Table results;
	  
//     std::string connectionID=connect();
	  
//     xdata::Table newRows;
	  
//     //get the definition of the table, so we know what data types should be in each row
//     getDefinition(connectionID,newRows);
	  
//     //add some random rows into the table definition
//     //the RandomData class is part of the TStoreTest application
//     RandomData randomData;
//     randomData.insertRandomRowsIntoTable(newRows);
	  
//     //insert the new rows
//     insert(connectionID,newRows);
	  
//     disconnect(connectionID);
	  
//   } catch (xcept::Exception &e) {
//     LOG4CPLUS_ERROR(this->getApplicationLogger(),xcept::stdformat_exception_history(e));
//   }
// }


// void getDefinition(const std::string &connectionID,xdata::Table &results) throw (xcept::Exception) {
//   //the definition message is essentially the same as a query message.
//   //instead of retrieving a table full of results, we retrieve an empty table
//   //with the appropriate column names and types.
  
//   //we need to send some parameters which are specific to SQLView.
//   //these use the namespace tstore-view-SQL. 
  
//   //In general, you might have the view name in a variable, so you won't know the view class. In this
//   //case you can find out the view class using the TStore client library:
//   std::string viewClass=tstoreclient::classNameForView("urn:tstore-view-SQL:TStoreInsert");
  
//   TStoreRequest request("definition",viewClass);
  
//   //add the connection ID
//   request.addTStoreParameter("connectionID",connectionID);
  
//   //for an SQLView, the name parameter refers to the name of a insert section in the configuration
//   //since the definition is used for an insert.
//   //We'll use the "test" one.
//   request.addViewSpecificParameter("name","test");
  
//   xoap::MessageReference message=request.toSOAP();
//   xoap::MessageReference response=sendSOAPMessage(message);
  
//   //use the TStore client library to extract the first attachment of type "table"
//   //from the SOAP response
//   if (!tstoreclient::getFirstAttachmentOfType(response,results)) {
//     XCEPT_RAISE (xcept::Exception, "Server returned no data");
//   }
// }


// void insert(const std::string &connectionID,xdata::Table &newRows) throw (xcept::Exception) {
  
//   //for a query, we need to send some parameters which are specific to SQLView.
//   //these use the namespace tstore-view-SQL. 
  
//   //In general, you might have the view name in a variable, so you won't know the view class. In this
//   //case you can find out the view class using the TStore client library:
//   std::string viewClass=tstoreclient::classNameForView("urn:tstore-view-SQL:TStoreInsert");
	
//   //If we give the name of the view class when constructing the TStoreRequest, 
//   //it will automatically use that namespace for
//   //any view specific parameters we add.
//   TStoreRequest request("insert",viewClass);
	
//   //add the connection ID
//   request.addTStoreParameter("connectionID",connectionID);
	
//   //for an SQLView, the name parameter refers to the name of a query section in the configuration
//   //We'll use the "test" one.
//   request.addViewSpecificParameter("name","test");
	
//   xoap::MessageReference message=request.toSOAP();	
//   //add our new rows as an attachment to the SOAP message
//   //the last parameter is the ID of the attachment. The SQLView does not mind what it is, as there should only be one attachment per message.
//   tstoreclient::addAttachment(message,newRows,"test");
	
//   xoap::MessageReference response=sendSOAPMessage(message);
// }
