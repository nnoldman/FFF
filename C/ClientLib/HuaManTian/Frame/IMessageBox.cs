using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Frame {
public class MessageBoxParam {
    public object data;
    public Action<object> rightButtonCallback;
    public Action<object> leftButtonCallback;
    public string rightButtonText;
    public string leftButtonText;
    public string content;
    public string title = string.Empty;
    public bool useCancelButton = true;
}

public interface IMessageBox {
    void ShowBox(Frame.MessageBoxParam param);
}

}
