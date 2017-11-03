using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using UnityEngine;

namespace AppCore
{
    public enum GameError
    {
    }
    public class Flow
    {
        public delegate void ProcessDelegate(int cur, int max);
        public delegate void Tip(string tip);
        public static Flow Instance
        {
            get
            {
                if (mInstance == null)
                    mInstance = new Flow();
                return mInstance;
            }
        }
        public static Flow mInstance;
        public ProcessDelegate onProcess;
        public Tip onTip;
        private List<GameFrame.ProcedureBase> procedures_ = new List<GameFrame.ProcedureBase>();


        public void Clear()
        {
            procedures_.Clear();
        }
        public Configuration config
        {
            get;
            set;
        }
        public Game game
        {
            get;
            set;
        }
        public GameError error
        {
            get;
            set;
        }
        private AppState state
        {
            get;
            set;
        }

        public YieldEventHandler onStartEnd
        {
            get;
            set;
        }


        internal Flow()
        {
        }

        public void AddProcedure<T>()where T: GameFrame.ProcedureBase
        {
            var type = typeof(T);
            var creator = type.BaseType.GetField("Instance");
            var instance = Activator.CreateInstance<T>();
            creator.SetValue(null, instance);
            procedures_.Add(instance);
        }

        public IEnumerator Start()
        {
            for(int i = 0; i < procedures_.Count; ++i)
            {
                var procedure = procedures_[i];
                if (onTip != null)
                    onTip(procedure.GetTipText());
                if (onProcess != null)
                    onProcess(i, procedures_.Count);
                yield return procedure.Start();
                if (procedure.error)
                    yield break;
            }

            if (onProcess != null)
                onProcess(procedures_.Count, procedures_.Count);

            if (onStartEnd != null)
                yield return onStartEnd();
        }
    }
}
