#include "stdafx.h"
#include "Installer.h"
#include <windows.h>
#include <string>
#include <time.h>
#include <tchar.h>
#include <iostream>
#include <fstream>

using namespace std;
void  WriteLog(LPCTSTR path, LPCTSTR content)
{
    try
    {
        time_t tt = time(NULL);
        tm t;
        localtime_s(&t, &tt);
        wchar_t date[20];
        wcsftime(date, 20, _T("%Y-%m-%d %H:%M:%S"), &t);
        wofstream file;
        file.open(path, std::ios::app);
        if (file.is_open())
        {
            file.imbue(std::locale("chs"));
            file << date << _T(" ") << (content ? content : _T("")) << endl;
            file.close();
        }
    }
    catch (...)
    {
    }
}



Function(test_pureCall)
{
    //auto currentTime = time(nullptr);
    //for (int i = 0; i < 100; ++i)
    //{
    //    WriteLog(_T("purcCall.txt"), _T("xLua为Unity、 .Net、 Mono等C#环境增加Lua脚本编程的能力，借助xLua，这些Lua代码可以方便的和C#相互调用"));
    //}
    //std::cout << "Pass:" << time(nullptr) - currentTime << std::endl;
    //Person1* person = new Person1();
    //person->dec();
}
