#include "stdafx.h"
#include "AnyObject.h"
AnyObject::AnyObject()
	:object_(nullptr)
{
}


AnyObject::AnyObject(Any object)
{
	this->object_ = new Any(object);
}

AnyObject::AnyObject(const char* value)
{
	this->object_ = new Any(string(value));
}

AnyObject::AnyObject(AnyObject& other)
{
	this->object_ = other.object_;
	other.object_ = nullptr;
}

AnyObject::AnyObject(const AnyObject& other)
{
	if (other.object_)
		this->object_ = new Any(*other.object_);
	else
		this->object_ = new Any();
}

AnyObject & AnyObject::operator=(Any object)
{
	dSafeDelete(this->object_);
	this->object_ = new Any(object);
	return *this;
}

AnyObject& AnyObject::operator=(AnyObject& other)
{
	dSafeDelete(this->object_);
	if (other.object_)
		this->object_ = new Any(*other.object_);
	return *this;
}

AnyObject::~AnyObject()
{
	dSafeDelete(this->object_);
}

string AnyObject::toString()
{
	stringstream ret;
	if (this->object_)
	{
		const auto& id = this->object_->type();
		if (id == typeid(u8))
		{
			auto var = get<u8>();
			if (var)
				ret << *var;
		}
		else if (id == typeid(u16))
		{
			auto var = get<u16>();
			if (var)
				ret << *var;
		}
		else if (id == typeid(u32))
		{
			auto var = get<u32>();
			if (var)
				ret << *var;
		}
		else if (id == typeid(u64))
		{
			auto var = get<u64>();
			if (var)
				ret << *var;
		}
		else if (id == typeid(s8))
		{
			auto var = get<s8>();
			if (var)
				ret << *var;
		}
		else if (id == typeid(s16))
		{
			auto var = get<s16>();
			if (var)
				ret << *var;
		}
		else if (id == typeid(s32))
		{
			auto var = get<s32>();
			if (var)
				ret << *var;
		}
		else if (id == typeid(s64))
		{
			auto var = get<s64>();
			if (var)
				ret << *var;
		}
		else if (id == typeid(bool))
		{
			auto var = get<bool>();
			if (var)
				ret << *var;
		}
		else if (id == typeid(double))
		{
			auto var = get<double>();
			if (var)
				ret << *var;
		}
		else if (id == typeid(float))
		{
			auto var = get<float>();
			if (var)
				ret << *var;
		}
		else if (id == typeid(string))
		{
			auto var = get<string>();
			if (var)
				ret << *var;
		}
		else
		{
			assert(false && "Non Implement Type!"&&id.name());
		}
	}
	return ret.str();
}

bool AnyObject::isString() const
{
	if (this->object_ == nullptr)
		return false;
	return this->object_->type() == typeid(string);
}
