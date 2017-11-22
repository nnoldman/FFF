using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

public class Message {
    public class MessageBoxParam {
        public string content;
        public object data;
        public string leftButtonText = string.Empty;
        public string rightButtonText = string.Empty;
        public Action<object> leftButtonCallback;
        public Action<object> rightButtonCallback;
    }
    public static void ShowBox(MessageBoxParam param) {
        GameFrame.UIs.Instance.Get<MessageBoxView>().Open(param);
    }
}
