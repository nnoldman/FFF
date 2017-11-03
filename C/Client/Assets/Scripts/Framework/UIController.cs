using FairyGUI;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

namespace AppCore
{
    public class UIController: GameController<UIController>
    {
        public ViewBase mainView;
        private List<ViewBase> views_ = new List<ViewBase>();
        private Dictionary<string, ViewBase> cacheViews_ = new Dictionary<string, ViewBase>();
        private ViewBase currentView_;

        public T Show<T>(bool only = true) where T : ViewBase, new()
        {
            T ret = Get<T>();
            if(ret != null)
            {
                if (only)
                    Close();
                views_.Remove(ret);
                views_.Add(ret);
                currentView_ = ret;
                ret.Show();
            }
            return ret;
        }

        public void ShowView(ViewBase view, bool only)
        {
            if (only)
                Close();
            views_.Remove(view);
            views_.Add(view);
            currentView_ = view;
            view.Show();
        }

        public void Close()
        {
            GRoot.inst.CloseAllWindows();
            views_.Clear();
        }

        public void GoBack()
        {
            if(currentView_ != null)
            {
                currentView_.Hide();
                //GRoot.inst.RemoveChild(currentView_);
                Debug.Assert(views_[views_.Count - 1] == currentView_);
                views_.RemoveAt(views_.Count - 1);
            }
            if(views_.Count > 0)
            {
                currentView_ = views_[views_.Count - 1];
                currentView_.Show();
            }
            else
            {
                if(mainView != null)
                {
                    currentView_ = mainView;
                    views_.Add(mainView);
                    currentView_.Show();
                }
                else
                {
                    currentView_ = null;
                }
            }
        }

        public T Hide<T>() where T : ViewBase, new()
        {
            return default(T);
        }

        public T Get<T>() where T : ViewBase, new()
        {
            ViewBase ret = null;
            string name = typeof(T).Name;
            if(!cacheViews_.TryGetValue(name, out ret))
            {
                ret = LoadView<T>(name);
                cacheViews_.Add(name, ret);
            }
            return (T)ret;
        }

        public T LoadView<T>(string name) where T : ViewBase, new ()
        {
            T ret = new T();
            ret.Show();
            return ret;
        }

        public override IEnumerator Initialize()
        {
            UIConfig.defaultFont = "SimHei,Droid Sans Fallback, LTHYSZK, Helvetica-Bold, Microsoft YaHei";
            GRoot.inst.SetContentScaleFactor(576, 1024);
            UIPackage.AddPackage("UI/Basics");
            UIPackage.AddPackage("UI/Common");
            UIPackage.AddPackage("UI/CommonBack");
            UIPackage.AddPackage("UI/MessageBox");

            Common.CommonBinder.BindAll();
            CommonBack.CommonBackBinder.BindAll();
            Earth.EarthBinder.BindAll();
            Login.LoginBinder.BindAll();
            MainUI.MainUIBinder.BindAll();
            MessageBox.MessageBoxBinder.BindAll();
            UIConfig.globalModalWaiting = UIPackage.GetItemURL("MessageBox", "MessageBox");
            UIController.Instance.Show<TVView>(false);
            yield return null;
        }


        public override IEnumerator onGameStageClose()
        {
            throw new NotImplementedException();
        }
    }
}
