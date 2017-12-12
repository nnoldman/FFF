using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class GateWindow : MonoBehaviour, Frame.IProgressBar {
    private Image bar_;
    private Text tip_;
    private string operationText_;
    public static GateWindow Instance {
        get {
            if(instance_ == null) {
                var prefab = Resources.Load<GameObject>(GameOption.Gate.ProgressWindow);
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

    void Awake() {
        this.bar_ = transform.Find("ProgressBar").GetComponent<Image>();
        this.tip_ = transform.Find("Tip").GetComponent<Text>();
    }

    public void Hide() {
        gameObject.SetActive(false);
    }

    public void SetText(string text) {
        operationText_ = text;
    }

    public void Show() {
        gameObject.SetActive(true);
    }

    public void SetProgress(int value, int max, string fmt) {
        this.bar_.fillAmount = 1.0f * value / max;
        this.tip_.text = operationText_ + string.Format(fmt, value, max);
    }

    public void SetProgress(float value, string fmt) {
        this.bar_.fillAmount = value;
        this.tip_.text = operationText_ + string.Format(fmt, value);
    }
}
