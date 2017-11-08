using System;
using System.Collections.Generic;
using System.Collections;
using System.Linq;
using System.Text;
using System.Collections.Specialized;
using Cmd;
using UnityEngine;
public class ItemMoveParam
{
    public GameDefine.ObjectCellType cell;
    public int position;
    public ItemObject obj;
}
public class ItemCount
{
    public int count;
    public int id;

    public static List<ItemCount> Parse(string str)
    {
        string[] stritems = str.Split(';');
        List<ItemCount> ret = new List<ItemCount>();
        foreach (var stritem in stritems)
        {
            if (stritem.Length == 0)
                continue;
            var elements = stritem.Split(',');
            if (elements != null && elements.Length > 0)
            {
                ItemCount ic = new ItemCount();
                try
                {
                    ic.id = int.Parse(elements[0]);
                }
                catch (Exception exc)
                {
                    Debug.LogWarning(exc.Message);
                }
                if (elements.Length > 1)
                {
                    try
                    {
                        ic.count = int.Parse(elements[1]);
                    }
                    catch (Exception exc)
                    {
                        Debug.LogWarning(exc.Message);
                    }
                }
                ret.Add(ic);
            }
        }
        return ret;
    }
}
public class ItemSystem : SystemBase
{
    public static ItemSystem Instance;
    private OrderedDictionary objects_ = new OrderedDictionary();
    public OrderedDictionary objects
    {
        get
        {
            return this.objects_;
        }
    }
    public override void BindListeners()
    {
        Commands.Instance.Bind(Cmd.SERVERID.RTObject_Add, OnObjectAdd);
        Commands.Instance.Bind(Cmd.SERVERID.RTObject_Sync, OnObjectSync);
        Commands.Instance.Bind(Cmd.SERVERID.RTObject_Delete, OnObjectDelete);
        Commands.Instance.Bind(Cmd.SERVERID.RTObject_Move, OnObjectMove);
    }


    void OnObjectAdd(object args)
    {
        var proto = ParseCmd<Cmd.RetObjectAdd>(args);
        if(proto.objects != null)
        {
            for(int i = 0; i < proto.objects.Count; ++i)
            {
                var obj = proto.objects[i];
                this.objects_.Remove(obj.dbID);
                this.objects_.Add(obj.dbID, obj);
                GameEvents.Instance.Trigger(GameEventID.OnObjectAdd, obj);
            }
        }
    }
    void OnObjectSync(object args)
    {
        var proto = ParseCmd<Cmd.RetObjectSync>(args);
        if (proto.objects != null)
        {
            for (int i = 0; i < proto.objects.Count; ++i)
            {
                var data = proto.objects[i];
                var obj = (Cmd.ItemObject)this.objects_[data.dbID];
                if(obj != null)
                {
                    obj.count = data.count;
                    GameEvents.Instance.Trigger(GameEventID.OnObjectSync, obj);
                }
            }
        }
    }
    void OnObjectDelete(object args)
    {
        var proto = ParseCmd<Cmd.RetObjectDelete>(args);
        if (proto.objects != null)
        {
            for (int i = 0; i < proto.objects.Count; ++i)
            {
                var data = proto.objects[i];
                var obj = (Cmd.ItemObject)this.objects_[data];
                if (obj != null)
                {
                    this.objects_.Remove(data);
                    GameEvents.Instance.Trigger(GameEventID.OnObjectDelete, obj);
                }
            }
        }
    }
    public ItemObject GetObject(int dbID)
    {
        var ret = objects_[dbID];
        if (ret != null)
        {
            return (ItemObject)ret;
        }
        return null;
    }
    void OnObjectMove(object args)
    {
        var proto = ParseCmd<Cmd.RetObjectMove>(args);
        var operObject = GetObject(proto.dbID);
        if (operObject == null)
            return;
        var dstObject = GetObjectByPosition(proto.cell, proto.position);
        if (dstObject != null)
        {
            dstObject.cell = operObject.cell;
            dstObject.position = operObject.position;
        }

        {
            //原位置,可能为空
            ItemMoveParam param = new ItemMoveParam();
            param.cell = operObject.cell;
            param.position = operObject.position;
            param.obj = dstObject;
            GameEvents.Instance.Trigger(GameEventID.OnObjectMove, param);
        }

        operObject.cell = proto.cell;
        operObject.position = proto.position;

        {
            //目标位置
            ItemMoveParam param = new ItemMoveParam();
            param.cell = operObject.cell;
            param.position = operObject.position;
            param.obj = operObject;
            GameEvents.Instance.Trigger(GameEventID.OnObjectMove, param);
        }
    }
    public ItemObject GetObjectByPosition(GameDefine.ObjectCellType loacation, int x)
    {
        var iter = objects_.GetEnumerator();
        while (iter.MoveNext())
        {
            var obj = (ItemObject)iter.Value;
            if (obj.cell == loacation && obj.position == x)
            {
                return obj;
            }
        }
        return null;
    }
    public ItemCount CountByItemID(int id)
    {
        ItemCount cnt = new ItemCount();
        cnt.id = id;
        var iter = objects_.GetEnumerator();
        while (iter.MoveNext())
        {
            var obj = (ItemObject)iter.Value;
            if (obj.cell == GameDefine.ObjectCellType.ObjectCellType_Bag)
            {
                if (obj.itemid == id)
                {
                    cnt.count += obj.count;
                }
            }
        }
        return cnt;
    }
}

