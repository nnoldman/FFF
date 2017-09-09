#ifndef Config_h__
#define Config_h__

#include "ConfigInfo.h"
class COREAPI Config {
  public:
    Config();

    ~Config();
  public:
    AppConfiguratin login;
    CenterConfig center;
  public:

    bool initialize(const char* file);
};

#endif // Config_h__
