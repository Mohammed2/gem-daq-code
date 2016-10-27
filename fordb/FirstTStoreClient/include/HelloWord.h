#ifndef HelloWorld_h
#define HelloWorld_h
#include "xdaq/Application.h"

class HelloWorld: public xdaq::Application {
        public:
        
        XDAQ_INSTANTIATOR();
        
        HelloWorld(xdaq::ApplicationStub * s) throw (xdaq::exception::Exception);
};
#endif
