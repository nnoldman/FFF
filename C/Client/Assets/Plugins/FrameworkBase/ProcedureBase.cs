using System.Collections;
using System.Collections.Generic;
namespace GameFrame
{
    public class ProcedureBase
    {
        public bool error
        {
            get
            {
                return error_;
            }
        }
        protected bool error_ = false;

        public virtual IEnumerator Start()
        {
            yield return null;
        }
        public virtual string GetTipText()
        {
            throw new System.NotImplementedException(GetType().Name);
        }
    }

    public class Procedure<T> : ProcedureBase
    {
        public static T Instance;
    }
}
