#include <GEMDBAccess.h>
#include <TStoreRequest.h>
#include "toolbox/TimeInterval.h"
#include "tstore/client/AttachmentUtils.h"
#include "tstore/client/Client.h"
#include "xcept/tools.h"
#include "xgi/Utils.h"
#include "xgi/Method.h"
#include "xdaq/WebApplication.h"
#include "cgicc/HTMLClasses.h"
#include "SimpleWeb.h"
//#include "tstoretest/RandomData.h"

gem::utils::db::GEMDBAccess::GEMDBAccess()
{
}

gem::utils::db::GEMDBAccess::~GEMDBAccess()
{
}


// void gem::utils::db::GEMDBAccess::Default(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception) {
//   //a link to the call query method below
  
//   std::string method =
//     toolbox::toString("/%s/query",getApplicationDescriptor()->getURN().c_str());

//   //  std::string method2=
//   //    toolbox::toString("/%s/setParameter",getApplicationDescriptor()->getURN().c_str());
 
//   *out << cgicc::HTMLDoctype(cgicc::HTMLDoctype::eStrict) << std::endl;
//   *out << cgicc::html().set("lang", "en").set("dir","ltr") << std::endl;
//   //  *out << cgicc::title("Simple Query") << std::endl;
//   //  *out << cgicc::a("Query").set("href",method) << std::endl;

//   *out << cgicc::fieldset().set("style","font-size: 10pt; font-family: arial;");
//   *out << std::endl;
//   *out << cgicc::legend("Select the Run Number to display VFAT2 configuration") << cgicc::p() << std::endl;
//   *out << cgicc::form().set("method","GET").set("action", method) << std::endl;
//   *out << cgicc::input().set("type","text").set("name","value").set("value", myParameter_.toString());
//   *out << std::endl;
//   *out << cgicc::input().set("type","submit").set("value","Run Number") << std::endl;
//   *out << cgicc::form() << std::endl;
//   *out << cgicc::fieldset(); 
  
  
//   //  *out << "<a href=\"query\">Query</a>" << std::endl;
//   //  *out << "<a href=\"insert\">Insert</a>" << std::endl;
// }

//void gem::utils::db::GEMDBAccess::query(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception) {
 void gem::utils::db::GEMDBAccess::query(xdata::Table &results) throw (xgi::exception::Exception) {
  try {
    xdata::Table results;

    std::cout<<" Before the connection to DB  "<<std::endl;
    std::cout<<" Before the connection to DB  "<<std::endl;
    std::cout<<" Before the connection to DB  "<<std::endl;
    
    std::string connectionID=connect();

    std::cout<<" after connection to DB  "<<std::endl;
    std::cout<<" after connection to DB  "<<std::endl;
    std::cout<<" after connection to DB  "<<std::endl;

    SetView(connectionID,results);
    disconnect(connectionID);
    
    // cgicc::Cgicc cgi(in);
    // myParameter_ = cgi["value"]->getIntegerValue();
    // this->Default(in,out);

    // *out<<" Run Number selected:   "<<myParameter_.toString()<<std::endl;

    // *out << cgicc::table().set("class", "table");
    // *out << "<tr><h2><div align=\"center\">VFAT2 parameters</div></h2></tr>" << std::endl;
    // std::vector<std::string> columns=results.getColumns();
    // for (unsigned long rowIndex=0;rowIndex<results.getRowCount();rowIndex++ ) {
    //   if(results.getValueAt(rowIndex,"RUN_NUMBER")->toString() == myParameter_.toString()){
    // 	//	LOG4CPLUS_INFO(this->getApplicationLogger(),"\n");
    // 	*out<<" <tr>Index "<<rowIndex<<"</tr>"<<std::endl;
    // 	for (std::vector<std::string>::iterator column=columns.begin(); column!=columns.end(); ++column) {
    // 	  std::string value=results.getValueAt(rowIndex,*column)->toString();
    // 	  //	  LOG4CPLUS_INFO(this->getApplicationLogger(),*column+": "+value);
    // 	  *out<<"<tr>"<<std::endl;
    // 	  *out<<"<td>"<<*column<<":  "<<value<<"</td>"<<std::endl;
    // 	  *out<<"</tr>"<<std::endl;
    // 	}
    //   }
    // }
    // *out << "</tr>" << std::endl;
    // *out << cgicc::table() <<std::endl;;
    // *out << "</div>" << std::endl;
    // *out << cgicc::br()<< std::endl;
    // *out << cgicc::hr()<< std::endl;    
    
  } catch (xcept::Exception &e) {
    //    LOG4CPLUS_ERROR(this->getApplicationLogger(),xcept::stdformat_exception_history(e));
  }


}

// xoap::MessageReference gem::utils::db::GEMDBAccess::sendSOAPMessage(xoap::MessageReference &message) throw (xcept::Exception) {
//   xoap::MessageReference reply;
	
//   std::cout << "Message: " << std::endl;
//   message->writeTo(std::cout);
//   std::cout << std::endl;
	
//   try {
//     xdaq::ApplicationDescriptor * tstoreDescriptor = getApplicationContext()->getDefaultZone()->getApplicationDescriptor("tstore::TStore",0);
//     xdaq::ApplicationDescriptor * tstoretestDescriptor=this->getApplicationDescriptor();
//     reply = getApplicationContext()->postSOAP(message,*tstoretestDescriptor, *tstoreDescriptor);
//   } 
//   catch (xdaq::exception::Exception& e) {
//     //    LOG4CPLUS_ERROR(this->getApplicationLogger(),xcept::stdformat_exception_history(e));
//     XCEPT_RETHROW(xcept::Exception, "Could not post SOAP message. ", e);
//   }

//   std::cout << "Entry   1 " << std::endl;
	
//   xoap::SOAPBody body = reply->getSOAPPart().getEnvelope().getBody();
//   std::cout << "Entry   2 " << std::endl;
		
//   std::cout << std::endl << "Response: " << std::endl;
//   reply->writeTo(std::cout);
//   std::cout << std::endl;
//   std::cout << "Entry   3 " << std::endl;
	
//   if (body.hasFault()) {
//     XCEPT_RAISE (xcept::Exception, body.getFault().getFaultString());
//   }
//   return reply;
// }

std::string gem::utils::db::GEMDBAccess::connect() throw (xcept::Exception) {

  TStoreRequest request("connect");

  std::cout<<" entry 1 connect   "<<std::endl;
	
  //  add the view ID
  request.addTStoreParameter("id","urn:tstore-view-SQL:VFAT2");

  std::cout<<" entry 2 connect   "<<std::endl;
	
  //this parameter is mandatory. "basic" is the only value allowed at the moment
  request.addTStoreParameter("authentication","basic");
	
  std::cout<<" entry 3 connect   "<<std::endl;
  //login credentials in format username/password
  request.addTStoreParameter("credentials","CMS_GEM_APPUSER_R/GEM_Reader_2015");  // Development GEMDB
	
  std::cout<<" entry 4 connect   "<<std::endl;

  //connection will time out after 20 minutes
  toolbox::TimeInterval timeout(1200,0); 
  request.addTStoreParameter("timeout",timeout.toString("xs:duration"));
  std::cout<<" entry 5 connect   "<<std::endl;
	
  xoap::MessageReference message=request.toSOAP();

  std::cout<<" entry 6 connect   "<<std::endl;

  xoap::MessageReference response= sendSOAPMessage(message);

  std::cout<<" entry 7 connect   "<<std::endl;
	
  //use the TStore client library to extract the response from the reply
  return tstoreclient::connectionID(response);
}

void gem::utils::db::GEMDBAccess::disconnect(const std::string &connectionID) throw (xcept::Exception) {
  TStoreRequest request("disconnect");
  
  //add the connection ID
  request.addTStoreParameter("connectionID",connectionID);
  
  xoap::MessageReference message=request.toSOAP();
  
  //  SimpleWeb::sendSOAPMessage(message);
}

void gem::utils::db::GEMDBAccess::SetView(const std::string &connectionID,xdata::Table &results) throw (xcept::Exception) {
  //for a query, we need to send some parameters which are specific to SQLView.
  //these use the namespace tstore-view-SQL. 
	
  //In general, you might have the view name in a variable, so you won't know the view class. In this
  //case you can find out the view class using the TStore client library:
  std::string viewClass=tstoreclient::classNameForView("urn:tstore-view-SQL:VFAT2");
	
  //If we give the name of the view class when constructing the TStoreRequest, 
  //it will automatically use that namespace for
  //any view specific parameters we add.
  TStoreRequest request("query",viewClass);
  
  //add the connection ID
  request.addTStoreParameter("connectionID",connectionID);
  
  //for an SQLView, the name parameter refers to the name of a query section in the configuration
  request.addViewSpecificParameter("name","VFAT2Settings");
  
  xoap::MessageReference message=request.toSOAP();
  //  xoap::MessageReference response=sendSOAPMessage(message);
  
  //use the TStore client library to extract the first attachment of type "table"
  //from the SOAP response
  //  if (!tstoreclient::getFirstAttachmentOfType(response,results)) {
  //    XCEPT_RAISE (xcept::Exception, "Server returned no data");
  //  }
}


// void gem::utils::db::GEMDBAccess::setParameter(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception) {
//   try
//     {
//       cgicc::Cgicc cgi(in);
//       myParameter_ = cgi["value"]->getIntegerValue();
//       this->Default(in,out);
//       //      *out<<"  Parameter  "<<myParameter_<<std::endl;

//     }
//   catch (const std::exception & e)
//     {
//       XCEPT_RAISE(xgi::exception::Exception, e.what());
//     }	
// }



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
