#include "SimpleWeb.h"
XDAQ_INSTANTIATOR_IMPL(SimpleWeb)
SimpleWeb::SimpleWeb(xdaq::ApplicationStub * s)
throw (xdaq::exception::Exception): xdaq::Application(s) 
{
  xgi::bind(this,&SimpleWeb::Default, "Default");           
}
