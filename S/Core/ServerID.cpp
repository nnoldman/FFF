#include "stdafx.h"
#include "ServerID.h"
const string& ServerID::get()
{
    return id_;
}

void ServerID::set(const char* id)
{
    id_ = id;
}

string ServerID::id_ = "0";
