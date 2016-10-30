#include "SimpleWeb.h"
#include "TStoreRequest.h"
#include "toolbox/TimeInterval.h"
#include "tstore/client/AttachmentUtils.h"
#include "tstore/client/Client.h"
#include "xcept/tools.h"
#include "xgi/Utils.h"
#include "xgi/Method.h"
#include "xdaq/WebApplication.h"
#include "cgicc/HTMLClasses.h"
//#include "GEMDBAccess.h"

XDAQ_INSTANTIATOR_IMPL(SimpleWeb)
SimpleWeb::SimpleWeb(xdaq::ApplicationStub * s)
    throw (xdaq::exception::Exception): xdaq::Application(s) 
{
    xgi::bind(this,&SimpleWeb::Default, "Default");           
}

xoap::MessageReference SimpleWeb::sendSOAPMessage(xoap::MessageReference &message) throw (xcept::Exception) {
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

void SimpleWeb::Default(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception) {
  *out << cgicc::HTMLDoctype(cgicc::HTMLDoctype::eStrict) << std::endl;
  *out << cgicc::html().set("lang", "en").set("dir","ltr") << std::endl;
  *out << cgicc::title("Simple Web") << std::endl;
  *out << cgicc::a("Visit the XDAQ Web site").set("href","http://xdaq.web.cern.ch") << std::endl;

  getDBInfo();


}

void SimpleWeb::getDBInfo(){

  
  xoap::MessageReference ViewInfo = GEMDBobj.getViewInfo("VFAT2");
  xoap::MessageReference ConnectionInfo = sendSOAPMessage(ViewInfo);
  

  std::string connectionID = GEMDBobj.connect(ConnectionInfo);

  xdata::Table results;

  xoap::MessageReference responsemsg = GEMDBobj.SetViewInfo("VFAT2",connectionID);

  xoap::MessageReference responseInfo = sendSOAPMessage(responsemsg);

  GEMDBobj.SetView(responseInfo,results);

  unsigned long rowIndex=0;
  xdata::Serializable* s = results.getValueAt(rowIndex,"BIAS_IPREAMPIN");
  xdata::Serializable* s1 = results.getValueAt(rowIndex,"CR0_TRGMODE");
  std::cout<<" data of serializable  BIAS_IPREAMPIN "<<s->type()<<std::endl;
  std::cout<<" data of serializable  CR0_TRGMODE    "<<s1->type()<<std::endl;
    
  xoap::MessageReference disconnectmsg = GEMDBobj.disconnectmsg(connectionID);

  sendSOAPMessage(disconnectmsg);

  std::string::size_type sz;   // alias of size_t
  int int0 = std::stoi (s->toString(),&sz);

  std::cout<<" conversion to integer  "<<int0<<std::endl;

}



  


