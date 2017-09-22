#pragma once
class COREAPI ServerID
{
public:
    static const string& get();
    static void set(const char* id);
private:
    static string id_;
};

