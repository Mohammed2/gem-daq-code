#ifndef HelloWorld_h
#define HelloWorld_h
#include "xdaq/Application.h"
#include "GEMDBAccess.h"

class HelloWorld: public xdaq::Application {
        public:

       gem::utils::db::GEMDBAccess GEMDBAccessObj;
        
        XDAQ_INSTANTIATOR();
        
        HelloWorld(xdaq::ApplicationStub * s) throw (xdaq::exception::Exception);
};
#endif
