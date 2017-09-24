using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[Serializable]
public abstract class TableManager<T>
{
    // abstract functions need tobe implements.
    public abstract string TableName();
    public abstract int MakeKey(T obj);

    // the data arrays.
    protected T[] mItemArray;
    Dictionary<int, int> mKeyItemMap = new Dictionary<int, int>();

    // constructor.
    public TableManager()
    {
        // load from excel txt file.
        mItemArray = CSVParser.Parse<T>(TableName());

        // build the key-value map.
        for (int i = 0; i < mItemArray.Length; i++)
            mKeyItemMap[MakeKey(mItemArray[i])] = i;
    }

    // get a item base the key.
    public T Get(int key)
    {
        int itemIndex;
        if (mKeyItemMap.TryGetValue(key, out itemIndex))
            return mItemArray[itemIndex];
        return default(T);
    }
    public T Get(double key)
    {
        int itemIndex;
        if (mKeyItemMap.TryGetValue((int)key, out itemIndex))
            return mItemArray[itemIndex];
        return default(T);
    }

    public T Get(uint key)
    {
        int itemIndex;
        if (mKeyItemMap.TryGetValue((int)key, out itemIndex))
            return mItemArray[itemIndex];
        return default(T);
    }
    // get the item array.
    public T[] GetAllItem()
    {
        return mItemArray;
    }
}
