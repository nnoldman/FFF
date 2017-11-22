using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class GateWindow : MonoBehaviour, IProgressBar
{
    private Image bar_;
    private Text tip_;

    public static GateWindow Instance
    {
        get
        {
            if(instance_ == null)
            {
                var prefab = Resources.Load<GameObject>(GameConfig.Gate.ProgressWindow);
                var go = GameObject.Instantiate(prefab);
                go.transform.parent = CanvasRoot.root.transform;
                go.transform.localPosition = Vector3.zero;
                go.transform.localScale = Vector3.one;
                instance_ = go.GetComponent<GateWindow>();
            }
            return instance_;
        }
    }
    private static GateWindow instance_;

    void Awake()
    {
        this.bar_ = transform.Find("ProgressBar").GetComponent<Image>();
        this.tip_ = transform.Find("Tip").GetComponent<Text>();
    }

    public void Hide()
    {
        gameObject.SetActive(false);
    }

    public void SetProgress(int current, int max)
    {
        this.bar_.fillAmount = 1.0f * current / max;
    }

    public void SetText(string text)
    {
        this.tip_.text = text;
    }

    public void Show()
    {
        gameObject.SetActive(true);
    }
}
