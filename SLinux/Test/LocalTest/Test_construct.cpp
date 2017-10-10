#include "stdafx.h"
#include "Installer.h"

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

private:
	T* value_;
};

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

Any& Any::operator=(Any& other)
{
	if (this->holder_)
		delete this->holder_;
	if(other.holder_)
		this->holder_ = other.holder_->clone();
	return *this;
}

Any::~Any()
{
	delete holder_;
}

Function(Test_Construct)
{
	{
		Any var_int(5);
		Any var_int2;
		var_int2 = var_int;
	}
}