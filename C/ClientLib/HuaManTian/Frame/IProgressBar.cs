using UnityEngine;
using System.Collections;
namespace Frame {
public interface IProgressBar {
    void SetProgress(int value, int max, string fmt);
    void SetProgress(float value, string fmt);
    void SetText(string text);
    void Show();
    void Hide();
}
}

