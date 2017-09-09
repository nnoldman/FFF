#include "stdafx.h"
#include "Config.h"


Config::Config()
{
}


Config::~Config()
{
}

bool Config::initialize(const char* file)
{
    xml_load(file);

    xml_get_node("login")
    {
        xml_get_node("script")
        {
            xml_get_attr("open", login.script.open);
        }
        xml_get_node("db")
        {
            xml_get_attr("dbname", login.db.dbName);
            xml_get_attr("user", login.db.user);
            xml_get_attr("passwrod", login.db.password);
            xml_get_attr("host", login.db.host);
            xml_get_attr("port", login.db.port);
            xml_get_attr("autoCreateAccount", login.db.autoCreateAccount);
        }

        xml_get_node("net")
        {
            xml_get_attr("ip", login.net.ip);
            xml_get_attr("port", login.net.port);
            xml_get_attr("threadCount", login.net.threadCount);
        }
    }

    xml_get_node("center")
    {
        xml_get_node("script")
        {
            xml_get_attr("open", center.script.open);
        }

        xml_get_node("db")
        {
            xml_get_attr("dbname", center.db.dbName);
            xml_get_attr("user", center.db.user);
            xml_get_attr("passwrod", center.db.password);
            xml_get_attr("host", center.db.host);
            xml_get_attr("port", center.db.port);
            xml_get_attr("autoCreateAccount", login.db.autoCreateAccount);
        }

        xml_get_node("net")
        {
            int serverid = 0;
            xml_get_attr("id", serverid);

            NetConfig* net = new NetConfig();
            xml_get_attr("ip", net->ip);
            xml_get_attr("port", net->port);
            xml_get_attr("threadCount", net->threadCount);
            xml_get_attr("name", net->name);

            center.centers.Insert(serverid, net);
        }
    }

    return true;
}
