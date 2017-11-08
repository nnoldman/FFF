using GameFrame;
using CommonBack;
using FairyGUI;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

public class EarthView : View
{
    Earth.EarthMainView window_;


    WindowTemplete windowFrame
    {
        get
        {
            return (WindowTemplete)window_.frame_;
        }
    }

    protected override string GetPackageName()
    {
        return "Earth/EarthMainView";
    }

    protected override void OnCreate()
    {
        this.window_ = (Earth.EarthMainView)this.contentPane;
        this.windowFrame.title_.text = "星体";
        this.windowFrame.close_.onClick.Add(() => UIController.Instance.GoBack());
        this.windowFrame.clickarea_.onClick.Add(() => UIController.Instance.GoBack());
        InitPropertyNames();
    }

    void InitPropertyNames()
    {
        this.window_.propertyList_.RemoveChildrenToPool();
        for (var id = RolePropertyID.FitNess; id <= RolePropertyID.Botany; ++id)
        {
            var item = (Common.CommonProperty)this.window_.propertyList_.AddItemFromPool();
            item.name_.text = Language.Instance.GetPropertyName(id);
        }
    }

    void OnCommand(EventContext context)
    {
        if (context.sender == this.windowFrame.close_)
        {
        }
    }
    protected override void OnShowMe()
    {
        UpdateBase();
    }

    void UpdateBase()
    {
    }
}
