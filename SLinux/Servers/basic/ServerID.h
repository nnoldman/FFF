#ifndef ServerID_h__
#define ServerID_h__
#include <string>
class ServerID {
  public:
    static const std::string& get();
    static void set(const char* id);
  private:
    static std::string id_;
};

#endif // ServerID_h__
