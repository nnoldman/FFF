using UnityEngine;
using System.Collections;

public interface IProgressBar
{
    void SetProgress(int current, int max);
    void SetText(string text);
    void Show();
    void Hide();
}
