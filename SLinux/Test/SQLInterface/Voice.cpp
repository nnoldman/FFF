#include "stdafx.h"
#include "Voice.h"
#include <sapi.h>
//#include <sphelper.h>
#pragma comment(lib,"ole32.lib") //CoInitialize CoCreateInstance需要调用ole32.dll   
#pragma comment(lib,"sapi.lib") //sapi.lib在SDK的lib目录,必需正确配置  
void TestVoice() {
    ISpVoice * pVoice = NULL;
    //COM初始化：
    if (FAILED(::CoInitialize(NULL)))
        return;
    //获取ISpVoice接口：
    HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
    if (SUCCEEDED(hr)) {
        ISpObjectToken * pSpObjectToken = NULL;
        //if (SUCCEEDED(SpFindBestToken(SPCAT_VOICES, L"language=804", NULL, &pSpObjectToken)))	//	其中409英语，804汉语，411日语
        {
            SYSTEMTIME st;
            GetLocalTime(&st);
            pVoice->SetVoice(pSpObjectToken);
            WCHAR wsz[128];
            swprintf_s(wsz, 128, L"现在时间是<context ID=\"CHS_Date_ymdhms\">%.4d年%.02d月%.2d日</context>", st.wYear, st.wMonth, st.wDay);
            pVoice->Speak(wsz, SPF_IS_XML | SPF_ASYNC, NULL);//SPF_IS_XML
            pVoice->WaitUntilDone(INFINITE);
            pVoice->Release();
            if(pSpObjectToken)
                pSpObjectToken->Release();
            pVoice = NULL;
        }
    }
    //千万不要忘记：
    ::CoUninitialize();
    return;
}
Voice::Voice() {
    TestVoice();
}


Voice::~Voice() {
}
