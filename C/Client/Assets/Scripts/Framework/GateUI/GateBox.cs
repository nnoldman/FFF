using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class GateBox : MonoBehaviour, Frame.IMessageBox {
    public static GateBox Instance {
        get {
            if(instance_ == null) {
                var prefab = Resources.Load<GameObject>(GameOption.Gate.MessageBoxWindow);
                var go = GameObject.Instantiate(prefab);
                go.transform.parent = CanvasRoot.root.transform;
                go.transform.localPosition = Vector3.zero;
                go.transform.localScale = Vector3.one;
                instance_ = go.GetComponent<GateBox>();
                go.SetActive(false);
            }
            return instance_;
        }
    }
    private static GateBox instance_;

    private Text tip_;
    private Button ok_;
    private Button cancel_;

    private Frame.MessageBoxParam param_;

    void Awake() {
        this.tip_ = transform.Find("Tip").GetComponent<Text>();
        this.ok_ = transform.Find("Ok").GetComponent<Button>();
        this.cancel_ = transform.Find("Cancel").GetComponent<Button>();

        this.ok_.onClick.AddListener(OnOK);
        this.ok_.onClick.AddListener(OnCancel);
    }

    void OnOK() {
        this.Hide();
        if (param_ != null && param_.rightButtonCallback != null)
            param_.rightButtonCallback(param_.data);
    }

    void OnCancel() {
        this.Hide();
        if (param_ != null && param_.leftButtonCallback != null)
            param_.leftButtonCallback(param_.data);
    }

    public void Hide() {
        gameObject.SetActive(false);
    }

    public void Show() {
        gameObject.SetActive(true);
    }

    public void ShowBox(Frame.MessageBoxParam param) {
        this.param_ = param;
        this.tip_.text = param.content;
        this.ok_.GetComponentInChildren<Text>(true).text =
            string.IsNullOrEmpty(param.rightButtonText) ? Frame.FrameOption.Texts.confirm : param.rightButtonText;
        this.cancel_.GetComponentInChildren<Text>(true).text =
            string.IsNullOrEmpty(param.leftButtonText) ? Frame.FrameOption.Texts.cancel : param.leftButtonText;
        this.Show();
    }
}
