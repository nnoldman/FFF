#ifndef AnyValue_h__
#define AnyValue_h__

#include <typeinfo>
#include <string>
namespace Basic {
    class DefaultValue {
      public:
        template<typename T>
        static bool isString(T* var) {
            return false;
        }

        static bool isString(std::string* var) {
            return true;
        }

        template<typename T>
        static bool isNumber(T* var) {
            return false;
        }

        static bool isNumber(char* var) {
            return true;
        }
        static bool isNumber(unsigned char* var) {
            return true;
        }
        static bool isNumber(short* var) {
            return true;
        }
        static bool isNumber(unsigned short* var) {
            return true;
        }
        static bool isNumber(int* var) {
            return true;
        }
        static bool isNumber(unsigned int* var) {
            return true;
        }
        static bool isNumber(int64_t* var) {
            return true;
        }
    };

    class ValueHolder {
      public:
        virtual ~ValueHolder();

        virtual const std::type_info& type() const = 0;
        virtual ValueHolder* clone() const = 0;
        virtual bool isString() const = 0;
        virtual bool isNumber() const = 0;
    };

    template<typename T>
    class Holder : public ValueHolder {
      public:
        Holder(const T& var);
        Holder(const char* var);
        ~Holder();
        virtual ValueHolder* clone() const override;
        virtual const std::type_info& type() const override;
        virtual bool isString() const override;
        virtual bool isNumber() const override;
        T* getValue() const;
      private:
        T* value_;
    };

    template<typename T>
    Holder<T>::Holder(const char* var) {
        if (var)
            value_ = new std::string(var);
        else
            value_ = new std::string();
    }

    template<typename T>
    bool Holder<T>::isNumber() const {
        return DefaultValue::isNumber(this->value_);
    }

    template<typename T>
    bool Holder<T>::isString() const {
        return DefaultValue::isString(this->value_);
    }

    template<typename T>
    T* Holder<T>::getValue() const {
        return value_;
    }

    template<typename T>
    const std::type_info& Holder<T>::type() const {
        return typeid(T);
    }

    template<typename T>
    ValueHolder* Holder<T>::clone() const {
        return new Holder<T>(*value_);
    }


    template<typename T>
    Holder<T>::~Holder() {
        delete value_;
    }

    template<typename T>
    Holder<T>::Holder(const T& var) {
        value_ = new T(var);
    }

    class AnyValue {
      public:
        AnyValue();
        ~AnyValue();
        AnyValue(const AnyValue& other);
        AnyValue& operator=(AnyValue& other);
        AnyValue(const char* var);
        template<typename T>
        AnyValue(const T& var);
        template<typename T>
        T get() const;

        bool isString() const;
        bool isNumber() const;
        std::string toString() const;
      private:
        ValueHolder* holder_;
    };

    template<typename T>
    AnyValue::AnyValue(const T& var)
        : holder_(new Holder<T>(var)) {
    }

    template<typename T>
    T AnyValue::get() const {
        auto ptr = dynamic_cast<Holder<T>*>(holder_);
        return ptr ? *ptr->getValue() : T();
    }
}

#endif // AnyValue_h__
