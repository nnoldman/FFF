using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using UnityEngine;

namespace AppCore
{
    public class Game
    {
        private SceneParam mSceneParam;

        private static List<BaseController> controllers_ = new List<BaseController>();

        public T AddController<T>() where T: BaseController
        {
            var type = typeof(T);
            var creator = type.BaseType.GetField("Instance");
            var instance = Activator.CreateInstance<T>();
            creator.SetValue(null, instance);
            controllers_.Add(instance);
            return instance;
        }

        public IEnumerator Start()
        {
            for(int i = 0; i < controllers_.Count; ++i)
            {
                var controller = controllers_[i];
                yield return controller.Initialize();
            }
        }

        public IEnumerator Close()
        {
            yield return null;
        }

        public IEnumerator LoadScene(SceneParam param)
        {
            mSceneParam = param;
            OnSceneClose();
            yield return null;
            OnSceneOpen();
            yield return null;
        }


        public void OnSceneOpen()
        {
        }
        public void OnSceneClose()
        {
        }
        public void OnMapLoaded()
        {
        }
        public void OnHeroReady()
        {
        }

    }
}
