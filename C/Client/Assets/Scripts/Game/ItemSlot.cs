using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;
using FairyGUI;
using Cmd;


public class ItemParam
{
    [Flags]
    public enum TextUsage
    {
        None,
        Number = 1 << 0,
        ForceZero = 1 << 1 | Number,
        Number_Bag = 1 << 2,
        Number_Need_Bag = 1 << 3 | Number_Bag,
        Custom = 1 << 4,
    }

    public int itemID
    {
        get
        {
            return obj == null ? itemID_ : (int)obj.itemid  ;
        }
        set
        {
            itemID_ = value;
        }
    }

    public int itemCount
    {
        get
        {
            return obj == null ? count_ : (int)obj.count ;
        }
        set
        {
            count_ = value;
        }
    }

    public Cmd.ItemObject obj;

    public bool useTips = true;
    public TextUsage textUsage = TextUsage.Number;

    public bool useRightTopText = false;
    public bool useWhenClick = false;

    public string rightTopText = string.Empty;
    public string rightButtomText = string.Empty;

    private int itemID_ = 0;
    private int count_ = 0;

    public GameDefine.ObjectCellType serverType;  //服务器
    public ClientDefine.ObjectCellType clientType;  //客户端
    public int position;
    public bool canDrag = false;
}

public class ItemSlot : MonoBehaviour
{
    public ItemParam param
    {
        get
        {
            return param_;
        }
    }

    ItemParam param_;
    public GButton owner;
    bool initialized_ = false;
    void Awake()
    {

    }
    void Initialize()
    {
        if (!initialized_)
            initialized_ = true;
    }

    public void Set(ItemParam param)
    {
        param_ = param;
        UpdataAll();
    }

    void UpdataAll()
    {
        Initialize();
        if (param_ == null)
            return;
        UpdateByParams();
    }

    public void Clear()
    {
        if(this.owner != null)
        {
            this.owner.icon = string.Empty;
            this.owner.title = string.Empty;
        }
    }

    void UpdateByParams()
    {
        if(param_.obj == null && param_.serverType != GameDefine.ObjectCellType.ObjectCellType_None)
        {
            param_.obj = ItemSystem.Instance.GetObjectByPosition(param_.serverType, param_.position);
        }

        if (param_.itemID == 0)
        {
            Clear();
            return;
        }

        var itembase = ItemTable.Instance.Get(param_.itemID);
        if (itembase == null)
            return;
        this.owner.icon = itembase.Icon.ToString();

        if (param_.textUsage == ItemParam.TextUsage.Custom)
        {
            this.owner.title = param_.rightButtomText;
        }
        else if ((param_.textUsage & ItemParam.TextUsage.Number_Bag) == ItemParam.TextUsage.Number_Bag)
        {
            UpdateBagNumber();
        }
        else if (param_.textUsage == ItemParam.TextUsage.ForceZero)
        {
            this.owner.title = param_.itemCount.ToString();
        }
        else if (param_.textUsage == ItemParam.TextUsage.Number)
        {
            this.owner.title = param_.itemCount == 0 ? string.Empty : param_.itemCount.ToString();
        }
        else if (param_.textUsage == ItemParam.TextUsage.None)
        {
        }
    }

//void OnPress(bool pressed)
//{
//    if (param_.clientType == CommonDefine.ObjectCellType.OBJECTCELLTYPE_EXTRACTEXCHANGE)
//    {
//        if (pressed)
//        {
//            StopAllCoroutines();
//            StartCoroutine(ExtractExchange());
//            return;
//        }
//        else
//        {
//            StopAllCoroutines();
//        }
//    }
//}

//IEnumerator ExtractExchange()
//{
//    while(true)
//    {
//        if (param_.obj == null || param_.obj.dwNum < 1)
//            yield break;
//        yield return null;
//    }
//}

    void OnClick()
    {
        if (param_ == null)
            return;

        if (param_.clientType == ClientDefine.ObjectCellType.None)
            return;

        if (!param_.useTips || param_.itemID == 0)
            return;
        var itembase = ItemTable.Instance.Get(param_.itemID);
        if (itembase != null)
        {
            //TipsWindow tips = UIController.Instance.Get<TipsWindow>();  //调用TipsWindow脚本
            //tips.ShowWindow(false);
            //tips.Set(param_);
        }
        else
        {
            Debug.LogWarning(string.Format("道具：{0}不存在！", param_.itemID));
        }
    }

    void BindListeners()
    {
        GameEvents.Instance.Bind(GameEventID.OnObjectAdd, OnItemAdd);
        GameEvents.Instance.Bind(GameEventID.OnObjectDelete, OnItemDelete);
        GameEvents.Instance.Bind(GameEventID.OnObjectMove, OnItemMove);
        GameEvents.Instance.Bind(GameEventID.OnObjectSync, OnItemRefresh);
    }

    void OnEnable()
    {
        BindListeners();
        UpdataAll();
    }
    void OnDisable()
    {
        GameEvents.Instance.RemoveListener(this);
    }


    bool UseBagNumber()
    {
        if (param_ == null)
            return false;
        return ItemParam.TextUsage.Number_Bag == (param_.textUsage & ItemParam.TextUsage.Number_Bag);
    }

    void UpdateBagNumber()
    {
        if (!UseBagNumber())
            return;
        var itemcount = ItemSystem.Instance.CountByItemID(param_.itemID);
        string ret = string.Empty;
        if (param_.textUsage == ItemParam.TextUsage.Number_Need_Bag)
        {
            int curCount = itemcount.count;

            string fmt = curCount >= param_.itemCount ? "[00FF00]{0}/{1}[-]" : "[FF0000]{0}/{1}[-]";
            ret = string.Format(fmt, curCount, param_.itemCount);
        }
        else
        {
            string fmt = itemcount.count > 0 ? "[00FF00]{0}[-]" : "[FF0000]{0}[-]";
            ret = string.Format(fmt, itemcount.count);
        }
    }

    bool IsCell(Cmd.ItemObject obj)
    {
        if (param_ == null || obj == null)
            return false;
        return param_.serverType == obj.cell && param_.position == obj.position;
    }

    void OnItemDelete(object args)
    {
        var obj = (ItemObject)args;
        if (IsCell(obj))
        {
            Clear();
            param_.obj = null;
        }
        else if(UseBagNumber())
        {
            if(param_.itemID == obj.itemid)
            {
                UpdateBagNumber();
            }
        }
    }

    void OnItemAdd(object args)
    {
        var obj = (ItemObject)args;
        if (IsCell(obj))
        {
            param_.obj = obj;
            UpdateByParams();
        }
        else if (UseBagNumber())
        {
            if (param_.itemID == obj.itemid)
            {
                UpdateBagNumber();
            }
        }
    }

    void OnItemMove(object args)
    {
        var param = (ItemMoveParam)args;
        if( param_.position == param.position && param_.serverType == param.cell)
        {
            param_.obj = param.obj;
            UpdateByParams();
        }
    }

    void OnItemRefresh(object args)
    {
        var obj = (ItemObject)args;
        if (IsCell(obj))
        {
            param_.obj = obj;
            UpdateByParams();
        }
        else if (UseBagNumber())
        {
            if (param_.itemID == obj.itemid)
            {
                UpdateBagNumber();
            }
        }
    }
}
