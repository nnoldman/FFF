#include "stdafx.h"
#include "Installer.h"
#include <memory>
struct Car
{
    int count = 0;
    int run()
    {
        return ++this->count;
    }
};


Function(test_wake_ptr)
{
    std::weak_ptr<Car> weakptrCar;
    {
        std::shared_ptr<Car> ptrCar(new Car());
        assert(ptrCar);
        assert(ptrCar->run() == 1);
        assert(ptrCar.use_count() == 1);
        weakptrCar = ptrCar;
        assert(ptrCar.use_count() == 1);
        std::shared_ptr<Car> ptrCar2 = ptrCar;
        assert(ptrCar2.use_count() == 2);
        assert(!weakptrCar.expired());
        weakptrCar._Get()->run();
    }
    assert(weakptrCar.expired());
}
