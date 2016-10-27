#
# Makefile for gemsupervisor package
#
BUILD_HOME:=$(shell pwd)/../..

include $(XDAQ_ROOT)/config/mfAutoconf.rules
include $(XDAQ_ROOT)/config/mfDefs.$(XDAQ_OS)

include $(XDAQ_ROOT)/config/mfDefs.extern_coretools
include $(XDAQ_ROOT)/config/mfDefs.coretools
include $(XDAQ_ROOT)/config/mfDefs.extern_powerpack
include $(XDAQ_ROOT)/config/mfDefs.powerpack
include $(XDAQ_ROOT)/config/mfDefs.extern_worksuite
include $(XDAQ_ROOT)/config/mfDefs.worksuite

Project=fordb
Package=FirstTStoreClient
#LongPackage=HelloWorld
#ShortPackage=HelloWorld
PackageName=FirstTStoreClient

# ROOT Config
ROOTCFLAGS =$(shell root-config --cflags)
ROOTLIBS   =$(shell root-config --libs)
ROOTGLIBS  =$(shell root-config --glibs) 

Sources+=HelloTStore.cc TStoreRequest.cc GEMDBAccess.cc

DynamicLibrary=HelloTStore GEMDBAccess

IncludeDirs =$(BUILD_HOME)/$(Project)/$(Package)/include
IncludeDirs+=$(XDAQ_ROOT)/include
IncludeDirs+=$(uHALROOT)/include
IncludeDirs+=$(ROOTDIR)/include 

IncludeDirs = \
	$(TSTORE_CLIENT_INCLUDE_PREFIX) \
	$(TSTORE_UTILS_INCLUDE_PREFIX) \
	$(XERCES_INCLUDE_PREFIX) \
        $(LOG4CPLUS_INCLUDE_PREFIX) \
        $(CGICC_INCLUDE_PREFIX) \
        $(XCEPT_INCLUDE_PREFIX) \
        $(CONFIG_INCLUDE_PREFIX) \
        $(TOOLBOX_INCLUDE_PREFIX) \
        $(PT_INCLUDE_PREFIX) \
        $(XDAQ_INCLUDE_PREFIX) \
        $(XDATA_INCLUDE_PREFIX) \
        $(XOAP_INCLUDE_PREFIX) \
	$(XOAP_FILTER_INCLUDE_PREFIX) \
        $(XGI_INCLUDE_PREFIX) \
        $(MIMETIC_INCLUDE_PREFIX)

DependentLibraryDirs =$(XDAQ_ROOT)/lib
DependentLibraryDirs+=$(uHALROOT)/lib

LibraryDirs =$(XDAQ_ROOT)/lib
LibraryDirs+=$(uHALROOT)/lib

PROFILING_Flags =-pg
DEBUG_CFlags  =-O0 -g3 -fno-inline -fPIC
DEBUG_CCFlags =${DEBUG_CFlags}
GCC47Flags = -std=c++11 -std=gnu++11
GCC48Flags = -std=c++14 -std=gnu++14
UserCFlags  =-std=c++0x -std=gnu++0x ${ROOTCFLAGS}  ${DEBUG_CFlags}
UserCCFlags =-std=c++0x -std=gnu++0x ${ROOTCFLAGS}  ${DEBUG_CCFlags}
UserDynamicLinkFlags =$(ROOTLIBS)
UserStaticLinkFlags =

DEBUG_LIBS =profiler tcmalloc
DependentLibraries = log4cplus config xcept boost_system cactus_uhal_uhal xerces-c 
Libraries          = log4cplus config xcept xerces-c numa toolbox asyncresolv uuid 

include $(XDAQ_ROOT)/config/Makefile.rules
include $(XDAQ_ROOT)/config/mfRPM.rules
#include $(BUILD_HOME)/$(Project)/mfRPM_gem.rules
print-env:
	@echo BUILD_HOME    $(BUILD_HOME)
	@echo XDAQ_ROOT     $(XDAQ_ROOT)
	@echo XDAQ_OS       $(XDAQ_OS)
	@echo XDAQ_PLATFORM $(XDAQ_PLATFORM)
	@echo LIBDIR        $(LIBDIR)
	@echo ROOTCFLAGS    $(ROOTCFLAGS)
	@echo ROOTLIBS      $(ROOTLIBS)
	@echo ROOTGLIBS     $(ROOTGLIBS)
