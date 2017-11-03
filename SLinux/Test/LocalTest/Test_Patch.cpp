#include "stdafx.h"
#include "Installer.h"
#include <algorithm>
enum AlterType
{
    Delete,
    Add,
};
struct Patcher
{
    string name;
    size_t index;
    AlterType alterType;
};

size_t findIndex(const vector<string>& arr, size_t start, string text)
{
    size_t ret = -1;
    for (size_t i = start; i < arr.size(); ++i)
    {
        if (arr[i] == text)
        {
            ret = i;
            break;
        }
    }
    return ret;
}

int sorter(Patcher * a, Patcher * b)
{
    if (a->index < b->index)
        return 1;
    if (a->index == b->index && a->alterType < b->alterType)
        return 1;
    if (a->index == b->index && a->alterType == b->alterType)
        return 0;
    return 0;
}
//size_t findIndex(const vector<string>& arr, size_t start, string text)
//{
//    size_t ret = -1;
//    for (size_t i = start; i < arr.size(); ++i)
//    {
//        if (arr[i] == text)
//        {
//            ret = i;
//            break;
//        }
//    }
//    return ret;
//}

bool make_patch(const vector<string>& source, const vector<string>& dest, vector<Patcher*>& ret)
{
    ret.clear();

    auto finder = [](const vector<string>& arr, size_t start, string text)
    {
        size_t ret = -1;
        for (size_t i = start; i < arr.size(); ++i)
        {
            if (arr[i] == text)
            {
                ret = i;
                break;
            }
        }
        return ret;
    };

    for (size_t i = 0, start = 0; i < dest.size(); ++i)
    {
        auto cur = dest[i];
        auto index = finder(source, start, cur);
        if (index == -1)
        {
            Patcher* patcher = new Patcher();
            patcher->index = i;
            patcher->name = cur;
            patcher->alterType = AlterType::Add;
            ret.push_back(patcher);
        }
        else if (index > start)
        {
            start = index;
            ++start;
        }
    }

    for (size_t i = 0, start = 0; i < source.size(); ++i)
    {
        auto cur = source[i];
        auto index = finder(dest, start, cur);
        if (index == -1)
        {
            Patcher* patcher = new Patcher();
            patcher->index = i;
            patcher->name = cur;
            patcher->alterType = AlterType::Delete;
            ret.push_back(patcher);
        }
        else if (index > start)
        {
            start = index;
            ++start;
        }
    }
    std::sort(ret.begin(), ret.end(), sorter);
    return ret.size() > 0;
}



bool patch(const vector<string>& source, const vector<Patcher*> patchers, vector<string>& ret)
{
    ret.clear();
    ret.resize(source.size() + patchers.size());
    {
        size_t pindex = 0;
        while (pindex < patchers.size())
        {
            auto patcher = patchers[pindex];
            if (patcher->alterType == AlterType::Add)
            {
                assert(ret[patcher->index].length() == 0);
                ret[patcher->index] = patcher->name;
            }
            ++pindex;
        }
    }
    {
        size_t pindex = 0;
        size_t sourceIndex = 0;
        size_t index = 0;
        for (; index < ret.size();)
        {
            if (ret[index].length() == 0)
            {
                if (pindex < patchers.size())
                {
                    auto patcher = patchers[pindex];
                    if (patcher->alterType == AlterType::Delete)
                    {
                        if (patcher->index == sourceIndex)
                        {
                            ++sourceIndex;
                            ++pindex;
                        }
                        else
                        {
                            ret[index] = source[sourceIndex];
                            ++index;
                            ++sourceIndex;
                        }
                    }
                    else
                    {
                        if (patcher->index > index)
                        {
                            ret[index] = source[sourceIndex];
                            ++index;
                            ++sourceIndex;
                        }
                        ++pindex;
                    }
                }
                else
                {
                    break;
                }
            }
            else
            {
                ++index;
            }
        }
        while (index < ret.size())
            ret.pop_back();
    }
    return true;
}

void make_alter_cmds(const vector<string>& source, const vector<string>& dest, vector<string>& cmds, string table)
{
    cmds.clear();
    vector<string> remove_columns;
    vector<tuple<string, string>> add_columns;
    for (size_t i = 0, start = 0; i < dest.size(); ++i)
    {
        auto cur = dest[i];
        auto index = findIndex(source, start, cur);
        if (index == -1)
        {
            add_columns.push_back(tuple<string, string>(i == 0 ? "" : dest[i - 1], dest[i]));
        }
        else if (index > start)
        {
            start = index;
            ++start;
        }
    }

    for (size_t i = 0, start = 0; i < source.size(); ++i)
    {
        auto cur = source[i];
        auto index = findIndex(dest, start, cur);
        if (index == -1)
        {
            remove_columns.push_back(cur);
        }
        else if (index > start)
        {
            start = index;
            ++start;
        }
    }


}

Function(Test_Patch)
{
    //ALTER TABLE test ADD COLUMN c INT NOT NULL AFTER a
    //ALTER TABLE test ADD COLUMN id INT UNSIGNED NOT NULL auto_increment PRIMARY KEY FIRST
    //alter table `user_movement_log` drop column Gatewayid
    vector<string>   dest = { "xqs", "fps", "id", "xx", "value", "pp" };
    vector<string>   source = { "id", "name", "io", "value" };
    vector<Patcher*> patchers;
    vector<Patcher*> patchers2;

    make_patch(source, dest, patchers);
    make_patch(dest, source, patchers2);
    vector<string> ret;
    vector<string> ret2;
    patch(source, patchers, ret);
    patch(dest, patchers2, ret2);
    assert(ret.size() == dest.size());
    assert(ret2.size() == source.size());
    for (size_t i = 0; i < ret.size(); ++i)
    {
        assert(ret[i] == dest[i]);
    }
    for (size_t i = 0; i < ret2.size(); ++i)
    {
        assert(ret2[i] == source[i]);
    }
    vector<string> cmds;
    make_alter_cmds(source, dest, cmds, "game_role1");
    std::cout << std::endl;
    for (auto it : cmds)
        std::cout << it << std::endl;
    //std::cout << std::endl;
    //for (auto it : patchers)
    //{
    //    std::cout << "Patcher:" << it->name << " Index:" << it->index << " Type:" << it->alterType << std::endl;
    //}
}