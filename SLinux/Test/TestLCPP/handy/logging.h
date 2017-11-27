#pragma  once
#include <string>
#include <stdio.h>
#include <atomic>
#include "util.h"



namespace handy {

    struct Logger: private noncopyable {
        enum LogLevel {LFATAL=0, LERROR, LUERR, LWARN, LINFO, LDEBUG, LTRACE, LALL};
        Logger();
        ~Logger();
        void logv(int level, const char* file, int line, const char* func, const char* fmt ...);

        void setFileName(const std::string& filename);
        void setLogLevel(const std::string& level);
        void setLogLevel(LogLevel level) {
            level_ = std::min(LALL, std::max(LFATAL, level));
        }

        LogLevel getLogLevel() {
            return level_;
        }
        const char* getLogLevelStr() {
            return levelStrs_[level_];
        }
        int getFd() {
            return fd_;
        }

        void adjustLogLevel(int adjust) {
            setLogLevel(LogLevel(level_+adjust));
        }
        void setRotateInterval(long rotateInterval) {
            rotateInterval_ = rotateInterval;
        }
        static Logger& getLogger();
      private:
        void maybeRotate();
        static const char* levelStrs_[LALL+1];
        int fd_;
        LogLevel level_;
        long lastRotate_;
        std::atomic<int64_t> realRotate_;
        long rotateInterval_;
        std::string filename_;
    };
#ifdef NDEBUG
#define hlog(level, ...) \
    do { \
        if (level<=handy::Logger::getLogger().getLogLevel()) { \
            handy::Logger::getLogger().logv(level, __FILE__, __LINE__, __func__, __VA_ARGS__); \
        } \
    } while(0)
#else
#define hlog(level, ...) \
    do { \
        if (level<=handy::Logger::getLogger().getLogLevel()) { \
            snprintf(0, 0, __VA_ARGS__); \
            handy::Logger::getLogger().logv(level, __FILE__, __LINE__, __func__, __VA_ARGS__); \
        } \
    } while(0)

#endif

#define trace(...) hlog(handy::Logger::LTRACE, __VA_ARGS__)
#define debug(...) hlog(handy::Logger::LDEBUG, __VA_ARGS__)
#define info(...) hlog(handy::Logger::LINFO, __VA_ARGS__)
#define warn(...) hlog(handy::Logger::LWARN, __VA_ARGS__)
#define error(...) hlog(handy::Logger::LERROR, __VA_ARGS__)
#define fatal(...) hlog(handy::Logger::LFATAL, __VA_ARGS__)
#define fatalif(b, ...) do { if((b)) { hlog(handy::Logger::LFATAL, __VA_ARGS__); } } while (0)
#define check(b, ...) do { if((b)) { hlog(handy::Logger::LFATAL, __VA_ARGS__); } } while (0)
#define exitif(b, ...) do { if ((b)) { hlog(handy::Logger::LERROR, __VA_ARGS__); _exit(1); }} while(0)

#define setloglevel(l) handy::Logger::getLogger().setLogLevel(l)
#define setlogfile(n) handy::Logger::getLogger().setFileName(n)
}

