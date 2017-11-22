using GameFrame;
using CommonBack;
using FairyGUI;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
public class BagView : View {
    private GameBag.BagMain window_;
    private WindowTemplete windowFrame {
        get {
            return (WindowTemplete)window_.frame_;
        }
    }
    protected override string GetPackageName() {
        return "GameBag/BagMain";
    }
    protected override void OnCreate() {
        this.window_ = (GameBag.BagMain)this.contentPane;
        this.windowFrame.title_.text = "包裹";
        this.windowFrame.close_.onClick.Add(() => UIs.Instance.GoBack());
        this.window_.items_.itemRenderer = OnItemRender;
        this.window_.items_.numItems = (int)GameDefine.Capcity.Bag;
    }

    void OnItemRender(int index, GObject item) {
        ItemSlot slot = item.displayObject.gameObject.TryGetComponent<ItemSlot>();
        slot.owner = item.asButton;
        var itemparam = new ItemParam();
        itemparam.serverType = GameDefine.ObjectCellType.ObjectCellType_Bag;
        itemparam.clientType = ClientDefine.ObjectCellType.Bag;
        itemparam.position = index;
        slot.Set(itemparam);
        //slot.icon = (100 + index).ToString();
    }
}
