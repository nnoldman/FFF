#pragma once
#include <iostream>
#include <queue>
#include <vector>
#include <stdexcept>
#include <memory>

using std::queue;
using std::vector;
/** @brief ObjectPool
		T* p=new T();
			1:T::operator new(size_t) (If doesn't have this function,call system's.Acquire one memory and get the address P)
			2:p->T()
			3:return P
		delete p;
			1:p->~T();
			2:p->operator delete(p);
	@author nnboy,7/11/2014  23:56
	**/
namespace Basic
{

template <typename T>
class ObjectPool
{
public:
    ObjectPool ( int chunkSize = mDefaultChunkSize );
    ~ObjectPool();

    inline T* acquireObject();
    inline void releaseObject ( void* obj );

    int getFreeNum()
    {
        return mFreeList.size();
    }
    void allocateChunk ( int chunkSize = mDefaultChunkSize );
protected:
    class queue<T*> mFreeList;
    class vector<T*> mAllObjects;

    int mChunkSize;
    static const int mDefaultChunkSize = 32;
private:
    ObjectPool ( const ObjectPool<T>& rhs );
    ObjectPool & operator= ( const ObjectPool<T>& rhs );
};

template <typename T>
ObjectPool<T>::ObjectPool ( int chunkSize ) /*throw ( std::invalid_argument, std::bad_alloc )*/
    : mChunkSize ( chunkSize )
{
    if ( mChunkSize <= 0 )
    {
        throw std::invalid_argument ( "chunk size must be positive" );
    }
    allocateChunk ( mChunkSize );
}

template <typename T>
void ObjectPool<T>::allocateChunk ( int chunkSize )
{
    for ( int i = 0; i < chunkSize; ++i )
    {
        T * block = new T() ;
        mAllObjects.push_back ( block );
        mFreeList.push ( block );
    }
}


template <typename T>
ObjectPool<T>::~ObjectPool()
{
    for ( auto p : mAllObjects )
        delete ( p );
}

template <typename T>
inline T* ObjectPool<T>::acquireObject()
{
    if ( mFreeList.empty() )
        allocateChunk ( mChunkSize );
    T *pobj = mFreeList.front();
    mFreeList.pop();
    return pobj;
}

template <typename T>
inline void ObjectPool<T>::releaseObject ( void* obj )
{
    if ( obj != nullptr )
    {
        mFreeList.push ( ( T* ) obj );
    }
}
#define DeclareObjectPool(type) \
	public:\
	static Basic::ObjectPool<type> mPool##type;\
		static void* operator new ( unsigned int n )\
		{\
		return mPool##type.acquireObject();\
		}\
		static void operator delete ( void* p )\
		{\
		mPool##type.releaseObject ( p );\
		}

#define ImplementObjectPool(type) \
	Basic::ObjectPool<type> type::mPool##type();

#define ImplementObjectPoolN(type,n) \
	Basic::ObjectPool<type> type::mPool##type ( n );
}
