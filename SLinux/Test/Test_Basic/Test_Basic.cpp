// Test_Basic.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#define dMemoryZeroArray(arr) memset(arr,0,sizeof(arr))

int main() {

    char* addr[4];
    for (auto it : addr) {
        it = nullptr;
    }
    return 0;
}

