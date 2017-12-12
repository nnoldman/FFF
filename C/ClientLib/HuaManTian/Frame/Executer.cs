using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Frame {
/// <summary>
/// 全局执行者
/// </summary>
public class Executer {

    public static void SetProgressBar(IProgressBar bar) {
        currentProgressBar_ = bar;
    }

    public static void SetMessageBox(IMessageBox messageBox) {
        currentMessageBox_ = messageBox;
    }
    public static void SetErrorInterface(IErrorInterface errorInterface) {
        errorInterface_ = errorInterface;
    }

    public static void HideProgressBar() {
        if (currentProgressBar_ != null)
            currentProgressBar_.Hide();
    }

    public static void ShowProgressBar() {
        if (currentProgressBar_ != null)
            currentProgressBar_.Show();
    }

    public static void SetProgressText(string text) {
        if (currentProgressBar_ != null)
            currentProgressBar_.SetText(text);
    }

    public static void SetProgress(int value, int max, string fmt = "({0}/{1})") {
        if (currentProgressBar_ != null)
            currentProgressBar_.SetProgress(value, max, fmt);
    }
    public static void SetProgress(float value, string fmt) {
        if (currentProgressBar_ != null)
            currentProgressBar_.SetProgress(value, fmt);
    }
    public static void SetProgress(int value, string fmt = "{0}%") {
        if (currentProgressBar_ != null)
            currentProgressBar_.SetProgress(value, 100, fmt);
    }
    public static void ShowBox(MessageBoxParam param) {
        if (currentMessageBox_ != null)
            currentMessageBox_.ShowBox(param);
    }

    public void Error(string text) {
        if (errorInterface_ != null)
            errorInterface_.ShowError(text);
    }

    private static IProgressBar currentProgressBar_;
    private static IMessageBox currentMessageBox_;
    private static IErrorInterface errorInterface_;
}
}
