#ifndef Environment_h__
#define Environment_h__
#include <string>
#include <map>
using namespace std;
namespace Basic {
    class Environment {
      public:
        static void start();
        static std::string currentWorkDirectory();
        static int setCurrentWorkDirectory(const char* dir);
        static std::string getAppName();
        static const std::string& getAppFileFullName();
        static std::string appStoreDirectory();
        static void sleep(int millSeconds);
        static int createDirectory(const char *pszDir);
      protected:
        static void refreshName();
        static std::string& getSignalName(int sig);
        static void saveBackTrace(int sig);
        static void setCrashDumperHandler();
        static void installCrashReporter();
      private:
        static std::string appFileFullName_;
        static char spliter;
        static std::map<int, string> signalMap_;
    };
}
#endif // Environment_h__
