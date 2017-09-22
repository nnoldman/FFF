#pragma once

#include <io.h>
class FileLoader
{
public:
    FileLoader(void);
    ~FileLoader(void);

    bool	OpenFile(const char* name);
    u32	GetBufferSize();
    void	Close();
    void	ReadToBuffer(Char* buffer);
protected:
    FILE* mFile;
    u32 mFileSize;
};
inline FileLoader::FileLoader(void)
    : mFile(0)
{
    Close();
}

inline FileLoader::~FileLoader(void)
{
}

inline bool FileLoader::OpenFile(const char* name)
{
    CXASSERT_RETURN_FALSE(name);

    CXASSERT_RETURN_FALSE(!fopen_s(&mFile, name, "r"));
    fseek(mFile, 0, SEEK_END);
    mFileSize = ftell(mFile);
    fseek(mFile, 0, SEEK_SET);
    return true;
}



inline u32 FileLoader::GetBufferSize()
{
    return mFileSize;
}

inline void FileLoader::Close()
{
    if (mFile)
    {
        fclose(mFile);
        mFile = nullptr;
    }
}

inline void FileLoader::ReadToBuffer(Char* buffer)
{
    if (mFile && buffer)
    {
        fread(buffer, 1, mFileSize, mFile);
    }
}