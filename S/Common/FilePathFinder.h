#pragma once
namespace Basic {
class FilePathFinder {
  public:
    FilePathFinder(void);
    ~FilePathFinder(void);
    typedef void (*CallBack)(const char* /*filename*/);

    void find(const char* path, const char* ext, CallBack call);
  protected:
};
}

