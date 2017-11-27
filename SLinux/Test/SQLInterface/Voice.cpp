#include "stdafx.h"
#include "Voice.h"
#include <sapi.h>
//#include <sphelper.h>
#pragma comment(lib,"ole32.lib") //CoInitialize CoCreateInstance��Ҫ����ole32.dll   
#pragma comment(lib,"sapi.lib") //sapi.lib��SDK��libĿ¼,������ȷ����  
void TestVoice() {
    ISpVoice * pVoice = NULL;
    //COM��ʼ����
    if (FAILED(::CoInitialize(NULL)))
        return;
    //��ȡISpVoice�ӿڣ�
    HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
    if (SUCCEEDED(hr)) {
        ISpObjectToken * pSpObjectToken = NULL;
        //if (SUCCEEDED(SpFindBestToken(SPCAT_VOICES, L"language=804", NULL, &pSpObjectToken)))	//	����409Ӣ�804���411����
        {
            SYSTEMTIME st;
            GetLocalTime(&st);
            pVoice->SetVoice(pSpObjectToken);
            WCHAR wsz[128];
            swprintf_s(wsz, 128, L"����ʱ����<context ID=\"CHS_Date_ymdhms\">%.4d��%.02d��%.2d��</context>", st.wYear, st.wMonth, st.wDay);
            pVoice->Speak(wsz, SPF_IS_XML | SPF_ASYNC, NULL);//SPF_IS_XML
            pVoice->WaitUntilDone(INFINITE);
            pVoice->Release();
            if(pSpObjectToken)
                pSpObjectToken->Release();
            pVoice = NULL;
        }
    }
    //ǧ��Ҫ���ǣ�
    ::CoUninitialize();
    return;
}
Voice::Voice() {
    TestVoice();
}


Voice::~Voice() {
}
