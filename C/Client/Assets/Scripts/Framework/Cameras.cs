using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

namespace GameFrame
{
    public class Cameras : GameController<Cameras>
    {
        private Camera uguiCamera_;
        private Camera mainCamera_;
        public bool enableUGUICamera
        {
            get
            {
                return uguiCamera_ ? uguiCamera_.gameObject.activeInHierarchy && uguiCamera_.enabled : false;
            }
            set
            {
                if (uguiCamera_)
                {
                    uguiCamera_.gameObject.SetActive(value);
                }
            }
        }
        public override IEnumerator Initialize()
        {
            FindUGUICamera();
            FindMainCamera();
            yield return null;
        }
        void FindUGUICamera()
        {
            var go = GameObject.FindGameObjectWithTag("UGUICamera");
            if (go != null)
                uguiCamera_ = go.GetComponent<Camera>();
        }
        void FindMainCamera()
        {
            var go = GameObject.FindGameObjectWithTag("MainCamera");
            if (go == null)
            {
                CreateMainCamera();
            }
            else
            {
                mainCamera_ = go.GetComponent<Camera>();
                if (mainCamera_ == null)
                    mainCamera_ = go.AddComponent<Camera>();
            }
        }
        void CreateMainCamera()
        {
            GameObject cameraObject = new GameObject("MainCamera");
            mainCamera_ = cameraObject.AddComponent<Camera>();
            mainCamera_.depth = 1;
            mainCamera_.cullingMask = ~0;
            mainCamera_.clearFlags = CameraClearFlags.SolidColor;
            mainCamera_.backgroundColor = Color.gray;
            mainCamera_.orthographic = true;
            mainCamera_.nearClipPlane = -30;
            mainCamera_.farClipPlane = 30;
            mainCamera_.tag = "MainCamera";
        }
    }
}
