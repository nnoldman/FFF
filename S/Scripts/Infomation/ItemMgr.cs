using System.Collections.Generic;
using System.Linq;

public class ItemMgr
{
    private List<t_ObjectProto> mItemList = new List<t_ObjectProto>();
    private List<t_ObjectProto> mMaterialItems = new List<t_ObjectProto>();

    public delegate void ItemChange();
    public List<ItemChange> OnItemChange=new List<ItemChange>();

    public List<t_ObjectProto> materialItems
    {
        get
        {
            return mMaterialItems;
        }
    }
    public ItemMgr()
    {
        //RandomInit();
    }


    private void RandomInit()
    {
        //int[] ids = new int[] { 1001, 1002, 1003, 1004 };
        //for (int i = 0; i < 30; )
        //{
        //    StatItem dbData = new StatItem();
        //    dbData.dbID = i++;
        //    dbData.id = ids[Random.Range(0, ids.Length)];
        //    dbData.count = Random.Range(1, 100);
        //    _items.Add(dbData);
        //}
    }

    public void OnNet(t_stAddObjectListUnityUserCmdProto cmd)
    {
        foreach (var oper in cmd.userset)
        {
            ItemAction action = (ItemAction)oper.byActionType;
            switch (action)
            {
                case ItemAction.Add:
                    {
                        Informations.Instance.ItemMgr.AddItem(oper.obj);
                    }
                    break;
                case ItemAction.Update:
                    {
                        Informations.Instance.ItemMgr.UpdateItem(oper.obj);
                    }
                    break;
                case ItemAction.Delete:
                    {
                        Informations.Instance.ItemMgr.DeleteItem(oper.obj.qwThisID);
                    }
                    break;
            }
        }
        UpdateAllItems();
    }

    public void UpdateItem(t_ObjectProto item)
    {
        int index = mItemList.FindIndex((t_ObjectProto si) => { return si.qwThisID == item.qwThisID; });
        if (index != -1)
        {
            mItemList.RemoveAt(index);
            mItemList.Add(item);
        }
        else
        {
            string error = "道具不存在: " + item.dwObjectID.ToString() + " X:" + item.pos.x.ToString();
            ALog.logWarning(error);
        }
    }
    public void AddItem(t_ObjectProto item)
    {
        mItemList.Add(item);
    }
    public void DeleteItem(uint dwThisID)
    {
        int index = mItemList.FindIndex((t_ObjectProto si) => { return si.qwThisID == dwThisID; });
        mItemList.RemoveAt(index);
    }
    public List<t_ObjectProto> GetTypeItems(ItemType type)
    {
        if (type == ItemType.None)
            return mItemList;

        List<t_ObjectProto> typeitems = new List<t_ObjectProto>();
        foreach (t_ObjectProto dbdata in mItemList)
        {
            if (dbdata.itemDefine)
            {
                switch (type)
                {
                    case ItemType.Other:
                        {
                            if (dbdata.itemDefine.type > ItemType.Other)
                                typeitems.Add(dbdata);
                        }
                        break;
                    default:
                        {
                            if (dbdata.itemDefine.type == type)
                                typeitems.Add(dbdata);
                        }
                        break;
                }
            }
        }
        return typeitems;
    }
    public Data.ItemCount Count(int id)
    {
        Data.ItemCount cnt = new Data.ItemCount();
        cnt.id = id;
        foreach (var item in mItemList)
        {
            if (item.dwObjectID == id)
            {
                cnt.count += (int)item.dwNum;
            }
        }
        return cnt;
    }


    public void UpdateAllItems()
    {
        UpdateItemMaterial();

        foreach (var callback in OnItemChange)
            callback();
    }
    private void UpdateItemMaterial()
    {
        mMaterialItems.Clear();
        foreach (var item in mItemList)
        {
            GameData.ObjectBase def = GameData.ObjectBase.Get(item.dwObjectID);
            if (def)
            {
                if (def.type == ItemType.Material)
                {
                    mMaterialItems.Add(item);
                }
            }
        }
    }
}
