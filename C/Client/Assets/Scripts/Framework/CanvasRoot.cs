using UnityEngine;
using System.Collections;

public class CanvasRoot : MonoBehaviour
{
    private static CanvasRoot root_;
    public static CanvasRoot root
    {
        get
        {
            if(root_ == null)
            {
                var canvas = GameObject.Find("Canvas");
                if (canvas)
                    root_ = canvas.GetComponent<CanvasRoot>();
            }
            return root_;
        }
    }
}
