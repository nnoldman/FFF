#ifndef FILE_LOADER_H
#define FILE_LOADER_H
#include "Buffer.h"
#include <fstream>
namespace Basic {
    class FileLoader {
      public:
        FileLoader(void);
        ~FileLoader(void);

        bool open(const char* name);
        u32	GetBufferSize();
        void Close();
        char* getBuffer() const;
      protected:
        u32 mFileSize;
        Buffer buffer_;
    };
    inline FileLoader::FileLoader(void) {
        Close();
    }
    inline char* FileLoader::getBuffer() const {
        return buffer_.getBuffer();
    }
    inline FileLoader::~FileLoader(void) {
    }

    inline bool FileLoader::open(const char* name) {
        CXASSERT_RETURN_FALSE(name);
        std::ifstream ifs(name);
        if (ifs) {
            ifs.seekg(0, ios::end);
            size_t length = ifs.tellg();
            ifs.seekg(0, ios::beg);

            buffer_.reallocate(length);
            auto& ret = ifs.read(buffer_.getBuffer(), buffer_.capacity());
            if (ret) {
                ifs.close();
                return true;
            }
        }
        return false;
    }


    inline u32 FileLoader::GetBufferSize() {
        return mFileSize;
    }

    inline void FileLoader::Close() {
    }
}
#endif //FILE_LOADER_H