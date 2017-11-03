// LocalTest.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Installer.h"
class Stu
{
public:
    virtual int dec() = 0;
};

class Person1 : public Stu
{
public:
    Person1()
        : number_(1)
    {
    }

    int dec() override
    {
        return --number_;
    }
private:
    int number_;
};

int main()
{
    Person1* person = new Person1();
    person->dec();

    Installer::run();
    std::cout << std::endl;
    //system("pause");
    return 0;
}

