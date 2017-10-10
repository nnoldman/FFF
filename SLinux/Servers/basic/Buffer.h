#ifndef Buffer_h__
#define Buffer_h__

//-------------------------------------------------------------------------
/**
	@brief
	@author nnboy,29/9/2014  12:08
*/
namespace Basic
{
    class Buffer
    {
    public:
        Buffer();
        ~Buffer();
        Buffer(size_t byteCnt);
        void reallocate(size_t byteSize);
        void reallocateByElementCount(size_t cnt);
        void clear();
        inline void setElementByteCount(size_t size);
        inline size_t length();
        inline size_t size();
        inline size_t elementWidth();
        inline void setSize(size_t size);
        inline size_t capacity() const;
        inline char* getBuffer() const;
        inline char* currentPointer() const;
        inline wchar_t* getWChar();
        inline const char* c_str() const;
        inline void copyTo(void* dst);
        inline void copyFrom(void* src);
        inline void setChar(size_t idx, char c);
        inline bool getline(char* buffer, size_t size);
        template<typename T>
        void addElement(T v);
        template<typename T>
        void addElement(T* v, size_t cnt);

        size_t readInt(int& var);
        size_t write(int& var);
        size_t write(u32& var);
        size_t getPosition();
        size_t forwardPosition(int tranlate);

        template<typename T>
        inline void set(size_t idx, const T& v)
        {
            *((T*)&data_[idx * sizeof(T)]) = v;
        }

        template<typename T>
        inline T& get(size_t idx)
        {
            return* ((T*) &data_[idx * sizeof(T)]) ;
        }

        inline void zero()
        {
            dMemoryZero(data_, length());
        }
        explicit  operator bool() const
        {
            // test if _Ipfx succeeded
            return (ok_);
        }
    protected:
        inline void free()
        {
            if (data_ != nullptr)
            {
                delete[] data_;
                data_ = nullptr;
            }
        }
        inline void setElementCount(size_t count)
        {
            elementCount_ = count;
        }
    private:
        size_t capacity_;
        size_t position_;
        size_t elementWidth_;
        size_t elementCount_;
        bool ok_;
    protected:
        union
        {
            char* data_;
            wchar_t* mWData;
        };
    };
    inline size_t Buffer::length()
    {
        return capacity_ * elementWidth_;
    }
    inline char* Buffer::getBuffer() const
    {
        return data_;
    }

    inline char* Buffer::currentPointer() const
    {
        return (char*)(data_ + position_);
    }

    inline const char* Buffer::c_str() const
    {
        return (const char*) data_;
    }
    inline void Buffer::setElementByteCount(size_t size)
    {
        elementWidth_ = size;
    }

    inline void Buffer::copyTo(void* dst)
    {
        dMemoryCopy(dst, data_, elementCount_ * elementWidth_);
    }

    inline void Buffer::copyFrom(void* src)
    {
        dMemoryCopy(data_, src, capacity_ * elementWidth_);
    }
    template<typename T>
    inline void Buffer::addElement(T* v, size_t cnt)
    {
        dMemoryCopy(&data_[elementCount_ * elementWidth_], v, cnt * elementWidth_);
        elementCount_ += cnt;
    }

    template<typename T>
    inline void Buffer::addElement(T v)
    {
        * ((T*) &data_[elementCount_ * sizeof(T)]) = v;
        elementCount_++;
    }


    inline size_t Buffer::size()
    {
        return elementCount_;
    }
    inline size_t Buffer::elementWidth()
    {
        return elementWidth_;
    }

    inline void Buffer::setChar(size_t idx, char c)
    {
        assert(data_);
        data_[idx] = c;
    }

    inline bool Buffer::getline(char* buffer, size_t size)
    {
        ok_ = true;
        char* dst = buffer;
        size_t count = 0;
        while (position_ < capacity_&&count < size)
        {
            auto ch = data_[position_];
            if (ch == '\n')
            {
                position_++;
                break;
            }
            *dst = ch;
            dst++;
            position_++;
            count++;
        }
        if (position_ == capacity_)
            ok_ = false;
        return ok_;
    }

    inline size_t Buffer::capacity() const
    {
        return capacity_;
    }

    inline void Buffer::clear()
    {
        elementCount_ = 0;
        position_ = 0;
        ok_ = true;
        this->zero();
    }
    inline Buffer::Buffer(void)
    {
        data_ = 0;
        elementCount_ = 0;
		position_ = 0;
        capacity_ = 0;
        elementWidth_ = 1;
        ok_ = true;
    }
    inline Buffer::Buffer(size_t byteCnt)
    {
        data_ = 0;
        elementCount_ = 0;
		position_ = 0;
		capacity_ = byteCnt;
        elementWidth_ = 1;
        reallocate(capacity_);
    }


    inline Buffer::~Buffer(void)
    {
        this->free();
    }

    inline void Buffer::reallocate(size_t byteSize)
    {
        this->free();
        data_ = new char[byteSize];
        if (elementWidth_ <= 0)
            elementWidth_ = 1;
        capacity_ = byteSize / elementWidth_;
        this->zero();
    }

    inline void Buffer::reallocateByElementCount(size_t cnt)
    {
        this->free();
        capacity_ = cnt;
        data_ = new char[capacity_ * elementWidth_];
        this->zero();
    }

    inline void Buffer::setSize(size_t size)
    {
        elementCount_ = size;
    }

    inline wchar_t* Buffer::getWChar()
    {
        return mWData;
    }

    inline size_t Buffer::readInt(int& var)
    {
        var = (*(int*)(data_ + position_));
        position_ += 4;
        return position_;
    }

    inline size_t Buffer::write(int& var)
    {
        (*(int*)(data_ + position_)) = var;
        position_ += sizeof(int);
        return position_;
    }

    inline size_t Buffer::write(u32& var)
    {
        (*(u32*)(data_ + position_)) = var;
        position_ += sizeof(u32);
        return position_;
    }

    inline size_t Buffer::getPosition()
    {
        return position_;
    }

    inline size_t Buffer::forwardPosition(int tranlate)
    {
        position_ += tranlate;
        return position_;
    }
}
#endif // Buffer_h__
