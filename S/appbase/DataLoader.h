#ifndef DataLoader_h__
#define DataLoader_h__
#include <iostream>
#include <fstream>
#include "Buffer.h"
struct RecordBase
{
};
template<typename T>
class DataLoader
{
public:
    virtual ~DataLoader()
    {
        dSafeDeleteVector(sourceRecords_);
    }
    virtual const char* fileName() = 0;
    virtual int getKey(RecordBase* record) = 0;
    bool reload();
    const T* get(int key) const;
    const std::vector<T*>& all() const;
protected:
    std::map<int, T*> records_;
    std::vector<T*> sourceRecords_;
    std::vector<string> columns_;
};
template<typename T>
const std::vector<T*>& DataLoader<T>::all() const
{
    return sourceRecords_;
}
template<typename T>
const T* DataLoader<T>::get(int key) const
{
    auto iter = records_.find(key);
    if (iter != records_.end())
        return iter->second;
    return nullptr;
}
template<typename T>
bool DataLoader<T>::reload()
{
    dSafeDeleteVector(sourceRecords_);
    records_.clear();

    string path = this->fileName();
    path.insert(0, "../config/");
    std::ifstream ifs(path);
    if (ifs.is_open())
    {
        ifs.seekg(0, ios::end);
        size_t length = ifs.tellg();
        ifs.seekg(0, ios::beg);

        Basic::Buffer fileBuffer(length);
        if (!ifs.read(fileBuffer.getBuffer(), fileBuffer.capacity()))
        {
            ifs.close();

            Basic::Buffer lineBuffer(4096);
            if (fileBuffer.getline(lineBuffer.getBuffer(), lineBuffer.capacity()))
            {
                columns_.clear();
                Basic::split(lineBuffer.c_str(), "\t", columns_);
            }

            if (columns_.size() > 0)
            {
                T::initColumnIndices(columns_);

                lineBuffer.clear();
                std::vector<string> values;
                while (fileBuffer.getline(lineBuffer.getBuffer(), lineBuffer.capacity()))
                {
                    Basic::split(lineBuffer.c_str(), "\t", values);
                    T* t = new T();
                    t->from(values);
                    sourceRecords_.push_back(t);
                }

                for (auto i : sourceRecords_)
                {
                    records_.insert(std::make_pair(this->getKey(i), i));
                }
            }
            else
            {
                goto IOError;
            }
        }
        else
        {
            goto IOError;
        }
    }
IOError:
    {
    }
    return records_.size() > 0;
}

#endif // DataLoader_h__
