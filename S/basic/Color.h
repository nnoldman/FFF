#pragma once
union Color {
    struct {
        unsigned char B;
        unsigned char G;
        unsigned char R;
        unsigned char A;
    };
    u32 color;
    operator u32 () {
        return color;
    }
    static const u32 White = 0XFFFFFFFF;
    static const u32 Black = 0X00000000;
    static const u32 Red = 0XFF0000FF;
    static const u32 Green = 0XFF00FF00;
    static const u32 Blue = 0X0000FFFF;
};


