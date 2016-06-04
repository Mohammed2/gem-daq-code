#ifndef HelloWorld_h
#define HelloWorld_h

#ifndef DOXYGEN_IGNORE_THIS

#include "config/PackageInfo.h"

//namespace gem {
//  namespace supervisor {
namespace HelloWorld {

#define HELLOWORLD_VERSION_MAJOR 0
#define HELLOWORLD_VERSION_MINOR 1
#define HELLOWORLD_VERSION_PATCH 0
  //#define HELLOWORLD_PREVIOUS_VERSIONS
#undef HELLOWORLD_PREVIOUS_VERSIONS

#define HELLOWORLD_VERSION_CODE PACKAGE_VERSION_CODE(HELLOWORLD_VERSION_MAJOR,HELLOWORLD_VERSION_MINOR, HELLOWORLD_VERSION_PATCH)

#ifndef HELLOWORLD_PREVIOUS_VERSIONS
#define HELLOWORLD_FULL_VERSION_LIST PACKAGE_VERSION_STRING(HELLOWORLD_VERSION_MAJOR,HELLOWORLD_VERSION_MINOR, HELLOWORLD_VERSION_PATCH)
#else
#define HELLOWORLD_FULL_VERSION_LIST HELLOWORLD_PREVIOUS_VERSIONS "," PACKAGE_VERSION_STRING(HELLOWORLD_VERSION_MAJOR, HELLOWORLD_VERSION_MINOR,HELLOWORLD_VERSION_PATCH)
#endif
    
  const std::string package = "HelloWorld";
  const std::string versions = HELLOWORLD_FULL_VERSION_LIST;
  const std::string summary = "HelloWorld";
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
