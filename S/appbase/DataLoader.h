#ifndef DataLoader_h__
#define DataLoader_h__

template<typename T>
class DataLoader
{
public:
    virtual ~DataLoader() {}
    virtual const char* fileName() = 0;
    bool reload();
protected:
    std::map<int, T*> records_;
};

template<typename T>
bool DataLoader<T>::reload()
{
    string path = this->fileName();
    path.insert(0, "../config/");
    std::istream is(path);
    if (!is.good())
    {

    }
}

#endif // DataLoader_h__
