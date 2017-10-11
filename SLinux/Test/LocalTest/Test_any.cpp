#include "stdafx.h"
#include "Installer.h"

class DefaultValue
{
public:
	template<typename T>
	static T getValue();

	template<>
	static int getValue() { return 0; }
	template<>
	static bool getValue() { return false; }
};

class ValueHolder
{
public:
	virtual ~ValueHolder()
	{
	}

	virtual const std::type_info& type() const = 0;
	virtual ValueHolder* clone() const = 0;
};

template<typename T>
class Holder :public ValueHolder
{
public:
	Holder(const T& var);
	~Holder();
	virtual ValueHolder* clone() const override;

	virtual const std::type_info& type() const override;

	T* getValue() const;
private:
	T* value_;
};

template<typename T>
T* Holder<T>::getValue() const
{
	return value_;
}

template<typename T>
const std::type_info& Holder<T>::type() const
{
	return typeid(T);
}

template<typename T>
ValueHolder* Holder<T>::clone() const
{
	return new Holder<T>(*value_);
}


template<typename T>
Holder<T>::~Holder()
{
	delete value_;
}

template<typename T>
Holder<T>::Holder(const T& var)
{
	value_ = new T(var);
}

class Any
{
public:
	Any();
	~Any();
	Any(const Any& other);
	Any& operator=(Any& other);

	template<typename T>
	Any(const T& var);
	template<typename T>
	T get();
private:
	ValueHolder* holder_;
};

Any::Any()
	:holder_(nullptr)
{

}

template<typename T>
Any::Any(const T& var)
	:holder_(new Holder<T>(var))
{

}

Any::Any(const Any& other)
	: holder_(other.holder_ ? other.holder_->clone() : nullptr)
{

}

template<typename T>
T Any::get()
{
	auto ptr = dynamic_cast<Holder<T>*>(holder_);
	if (ptr)
	{
		return *ptr->getValue();
	}
	return DefaultValue::getValue<T>();
}

Any& Any::operator=(Any& other)
{
	if (this->holder_)
		delete this->holder_;
	if (other.holder_)
		this->holder_ = other.holder_->clone();
	return *this;
}

Any::~Any()
{
	delete holder_;
}

Function(Test_Construct)
{
	Any var_int5(5);
	AssertTrue(var_int5.get<int>() == 5);
	Any var_int3 = 3;
	AssertTrue(var_int3.get<int>() == 3);
	var_int3 = var_int5;
	AssertTrue(var_int3.get<int>() == 5);
	AssertTrue(var_int5.get<int>() == 15);
}