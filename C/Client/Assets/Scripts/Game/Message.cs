using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

public class Message {

    public static void ShowBox(Frame.MessageBoxParam param) {
        GameFrame.UIs.Instance.Get<MessageBoxView>().Open(param);
    }
}
