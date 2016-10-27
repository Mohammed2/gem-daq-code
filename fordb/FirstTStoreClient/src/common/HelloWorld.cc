#include "HelloWorld.h"
#include "xdata/Table.h"

XDAQ_INSTANTIATOR_IMPL(HelloWorld)
HelloWorld::HelloWorld(xdaq::ApplicationStub * s)
    throw (xdaq::exception::Exception): xdaq::Application(s) 
{
    LOG4CPLUS_INFO(this->getApplicationLogger(),"Hello World!");            

    xdata::Table VFAT2ParamDB;
    //    GEMDBAccessObj.query(VFAT2ParamDB);
    
}
