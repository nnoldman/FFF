// Test_Basic.cpp : 定义控制台应用程序的入口点。
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

