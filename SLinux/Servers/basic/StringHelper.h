#ifndef StringHelper_h__
#define StringHelper_h__
#include "Buffer.h"
#include "CharBuffer.h"

namespace Basic {
    namespace StringHelper {
        template<typename T>
        void toString(std::string& dst, T* var) {
            dst = to_string(*var);
        }
        void toString(std::string& dst, std::string* var);
        void toString(std::string& dst, bool* var);


        void setValue(const char* val, std::string* var);
        void setValue(const char* val, int* var);
        void setValue(const char* val, float* var);
        void setValue(const char* val, bool* var);
        void setValue(const char* val, unsigned int* var);
        void setValue(const char* val, long* var);
        void setValue(const char* val, char* var);
        void setValue(const char* val, u8* var);
        void setValue(const char* val, u16* var);
        void setValue(const char* val, s16* var);
        void setValue(const char* val, u64* var);
        void setValue(const char* val, s64* var);
        void setValue(const char* val, double* var);

        template<int N>
        inline void toString(std::string& dst, CharBuffer<N>* var) {
            assert(var);
            dst = var->getString();
        }

        template<int N>
        inline void setValue(const char* val, CharBuffer<N>* var) {
            var->setString(val);
        }
    }
    inline void StringHelper::toString(std::string& dst, std::string* var) {
        assert(var);
        dst = var->c_str();
    }
    inline void StringHelper::toString(std::string& dst, bool* var) {
        dst = (*var) ? "true" : "false";
    }

    inline void StringHelper::setValue(const char* val, std::string* var) {
        assert(val);
        *var = val;
    }

    inline void StringHelper::setValue(const char* val, int* var) {
        if (val == nullptr)
            *var = 0;
        else if (strlen(val) == 0)
            *var = 0;
        else {
            try {
                *var = std::stoi(val);
            } catch (std::exception e) {
                *var = 0;
            }
        }
    }

    inline void StringHelper::setValue(const char* val, float* var) {
        try {
            *var = std::stof(val);
        } catch (std::exception e) {
            *var = 0;
        }
    }

    inline void StringHelper::setValue(const char* val, bool* var) {
        *var = !strcmp("True", val) || !strcmp("true", val);
    }

    inline void StringHelper::setValue(const char* val, unsigned int* var) {
        assert(val);
#if WIN32
        sscanf_s(val, "%u", var);
#elif __GNUC__
        sscanf(val, "%u", var);
#endif
    }

    inline void StringHelper::setValue(const char* val, long* var) {
        *var = std::stol(val);
    }

    inline void StringHelper::setValue(const char* val, char* var) {
        *var = (s8)std::stoi(val);
    }

    inline void StringHelper::setValue(const char* val, u8* var) {
        *var = (u8)std::stoi(val);
    }

    inline void StringHelper::setValue(const char* val, u16* var) {
        *var = (u16)std::stoi(val);
    }
    inline void StringHelper::setValue(const char* val, u64* var) {
        *var = (u64)std::stoull(val);
    }
    inline void StringHelper::setValue(const char* val, double* var) {
        *var = std::stod(val);
    }
    inline void StringHelper::setValue(const char* val, s16* var) {
        *var = (s16)std::stoi(val);
    }
    inline void StringHelper::setValue(const char* val, s64* var) {
        *var = (s64)std::stoll(val);
    }

}
#endif // StringHelper_h__
