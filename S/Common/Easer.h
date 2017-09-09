#pragma once
class Easer
{
public:
    float getEase(float start, float end, float elapsedTime, float totalTime);
};

inline float Easer::getEase(float start, float end, float elapsedTime, float totalTime)
{
    return start + (end - start) * sinf(elapsedTime / totalTime * 3.1415926535 * 0.5);
}
extern Easer gEaser;
DefineOnce Easer gEaser;


