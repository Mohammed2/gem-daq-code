#ifndef SimpleWeb_h
#define SimpleWeb_h
#include "xdaq/WebApplication.h"
#include "xgi/Method.h"
#include "cgicc/HTMLClasses.h"
class SimpleWeb: public xdaq::Application {
        public:
        
        XDAQ_INSTANTIATOR();
        
        SimpleWeb(xdaq::ApplicationStub * s) throw (xdaq::exception::Exception);
        void Default(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);

        private:

	xoap::MessageReference sendSOAPMessage(xoap::MessageReference &message) throw (xcept::Exception);

	
};
#endif
