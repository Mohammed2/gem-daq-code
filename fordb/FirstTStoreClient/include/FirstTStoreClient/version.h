#ifndef FirstTStoreClient_h
#define FirstTStoreClient_h

#ifndef DOXYGEN_IGNORE_THIS

#include "config/PackageInfo.h"

//namespace gem {
//  namespace supervisor {
namespace HelloWorld {

#define FIRSTTSTORECLIENT_VERSION_MAJOR 0
#define FIRSTTSTORECLIENT_VERSION_MINOR 1
#define FIRSTTSTORECLIENT_VERSION_PATCH 0
  //#define FIRSTTSTORECLIENT_PREVIOUS_VERSIONS
#undef FIRSTTSTORECLIENT_PREVIOUS_VERSIONS

#define FIRSTTSTORECLIENT_VERSION_CODE PACKAGE_VERSION_CODE(FIRSTTSTORECLIENT_VERSION_MAJOR,FIRSTTSTORECLIENT_VERSION_MINOR, FIRSTTSTORECLIENT_VERSION_PATCH)

#ifndef FIRSTTSTORECLIENT_PREVIOUS_VERSIONS
#define FIRSTTSTORECLIENT_FULL_VERSION_LIST PACKAGE_VERSION_STRING(FIRSTTSTORECLIENT_VERSION_MAJOR,FIRSTTSTORECLIENT_VERSION_MINOR, FIRSTTSTORECLIENT_VERSION_PATCH)
#else
#define FIRSTTSTORECLIENT_FULL_VERSION_LIST FIRSTTSTORECLIENT_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(FIRSTTSTORECLIENT_VERSION_MAJOR, FIRSTTSTORECLIENT_VERSION_MINOR,FIRSTTSTORECLIENT_VERSION_PATCH)
#endif
    
  const std::string package = "FirstTStoreClient";
  const std::string versions = FIRSTTSTORECLIENT_FULL_VERSION_LIST;
  const std::string summary = "FirstTStoreClient";
  const std::string description = "";
  const std::string authors = "Castaned";
  const std::string link = "";
    
  config::PackageInfo getPackageInfo();
  void checkPackageDependencies() throw (config::PackageInfo::VersionException);
  std::set<std::string, std::less<std::string> > getPackageDependencies();
  //  }
}

#endif // DOXYGEN_IGNORE_THIS

#endif // gem_supervisor_version_h
