#include "stdafx.h"
#include "Encrypt.h"
#include "md5.h"

string Encrypt::makeLoginToken(int accountID,int time)
{
    stringstream ss;
    ss << accountID;
    ss << time;
    ss << 0X93981382;
    MD5 md5(ss.str());
    return md5.toStr();
}
