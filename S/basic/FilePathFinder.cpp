#include "base.h"
#include "FilePathFinder.h"
#include <io.h>
#include "FileName.hpp"
#include <windows.h>
#include "Platform.h"
namespace Basic
{

FilePathFinder::FilePathFinder(void)
{
}


FilePathFinder::~FilePathFinder(void)
{
}


void FilePathFinder::find(const char* path, const char* ext, CallBack call)
{
    if (!path || !ext || !call)
        return;

    _finddata_t allFile;
    intptr_t hFile;
    uString target = path;
    target += "/*.*";//直接用*.txt之类的无法搜到子目录

    uString filename;

    if ((hFile = _findfirst(target.c_str(), &allFile)) == -1L)
        printf("Maybe path is error!\n");
    else
    {
        do
        {
            filename = path;
            filename += "/";
            filename += allFile.name;
            if (!dStrEqual(allFile.name, ".") && !dStrEqual(allFile.name, ".."))
            {
                FileName pather(filename.c_str());
                uString parentPath;
                if (Platform::isPath(filename.c_str()))
                {
                    if (pather.GetParentPath(parentPath))
                    {
                        find(pather.getOrignalName(), ext, call);
                    }
                    else
                    {
                    }
                }
                else
                {
                    if (filename.end_with(ext))
                        call(filename.c_str());
                    //if ( pather.GetParentPath ( parentPath ) )
                    //{
                    //}
                    //else
                    //{
                    //}
                }
            }
        }
        while (_findnext(hFile, &allFile) == 0);
        _findclose(hFile);
    }
}
}
