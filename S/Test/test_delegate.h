#pragma once
#include "Delegate.h"
#include <functional>


class test_delegate {
  public:
    test_delegate();

    void onOpenUI() {
        printf("test_delegate::onOpenUI =>Empty\n");
    }

    void onOpenUI(int arg1) {
        printf("test_delegate::onOpenUI =>%d\n", arg1);
    }
    void onOpenUI(int arg1, int arg2) {
        printf("test_delegate::onOpenUI =>%d,%d\n", arg1, arg2);
    }

    void onOpenUI(int arg1, int arg2, int arg3) {
        printf("test_delegate::onOpenUI =>%d,%d,%d\n", arg1, arg2, arg3);
    }
    ~test_delegate();
};

