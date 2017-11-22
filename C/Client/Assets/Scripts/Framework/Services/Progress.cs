using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

public class Progress
{
    public static Progress Instance
    {
        get
        {
            if (mInstance == null)
                mInstance = new Progress();
            return mInstance;
        }
    }

    public static Progress mInstance;

    public delegate void OperatonDelegate(string act, bool progress);
    public delegate void UpdateStateDelegate(bool updating);
    public delegate void ProgressDelegate(int cur, int max, bool percent1 = true, int allCurrent = 0, int all = 0, bool percent2 = true);

    public event OperatonDelegate OnOperationChange;
    public event UpdateStateDelegate OnUpdateStateChange;
    public event ProgressDelegate OnUpdate;

    public void Update(int cur, int max, bool percent1 = true, int allCurrent = 0, int all = 0, bool percent2 = true)
    {
        if(OnUpdate != null)
            OnUpdate(cur, max, percent1, allCurrent, all, percent2);
    }

    public void SetUpdateState(bool updating)
    {
        if(OnUpdateStateChange != null)
            OnUpdateStateChange(updating);
    }

    public void Operator(string act, bool progress)
    {
        if(OnOperationChange != null)
            OnOperationChange(act, progress);
    }
}
