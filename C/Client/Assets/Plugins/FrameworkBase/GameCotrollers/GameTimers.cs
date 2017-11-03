using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

public class GameTimers
{
    public float now
    {
        get
        {
            return mNow;
        }
    }
    public float deltaTime
    {
        get
        {
            return mDeltaTime;
        }
    }
    public bool needUpdate = true;
    private float mDeltaTime;
    private float mNow;
    private Dictionary<int, GameTimer> mTimers = new Dictionary<int, GameTimer>();
    private int mTimerCount;

    private static GameTimers mInstance;
    public static GameTimers Instance
    {
        get
        {
            if (mInstance == null)
                mInstance = new GameTimers();
            return mInstance;
        }
    }

    public void Clean()
    {
        mTimers.Clear();
    }

    public void OnFocus()
    {
        AdvanceTime(UnityEngine.Time.realtimeSinceStartup);
    }

    public void AdvanceTime(float currentTime)
    {
        if (!needUpdate)
            return;
        needUpdate = false;
        mDeltaTime = (currentTime - now) * 1000;
        mNow = currentTime;

        var enumerator = mTimers.GetEnumerator();
        try
        {
            while (enumerator.MoveNext() && !enumerator.Current.Value.isGarbage)
                enumerator.Current.Value.AdvanceTime(mDeltaTime);
        }
        catch (System.Exception ex)
        {
            UnityEngine.Debug.LogWarning(ex.Message);
        }

        enumerator = mTimers.GetEnumerator();
        while (enumerator.MoveNext())
        {
            if (enumerator.Current.Value != null && enumerator.Current.Value.isGarbage)
            {
                mTimers.Remove(enumerator.Current.Key);
                enumerator = mTimers.GetEnumerator();
            }
        }
    }

    GameTimer RequireTimer()
    {
        GameTimer timer = new GameTimer();
        timer.id = ++mTimerCount;
        mTimers.Add(timer.id, timer);
        return timer;
    }

    public GameTimer Add(float leftTime, float duration = 0.3f)
    {
        if (leftTime < 0)
            leftTime = 0;
        var timer = RequireTimer();
        timer.totalTimeMS = leftTime * 1000;
        timer.intervalMS = duration * 1000;
        timer.loop = false;
        timer.Start();
        return timer;
    }

    public GameTimer AddTimer(float leftTime, float totalTime, float duration = 0.3f)
    {
        if (leftTime < 0)
            leftTime = 0;
        var timer = RequireTimer();
        timer.totalTimeMS = totalTime * 1000;
        timer.passSeconds = (totalTime - leftTime);
        timer.intervalMS = duration * 1000;
        timer.loop = false;
        timer.Start();
        return timer;
    }

    public GameTimer Invoke( float leftTime, Action onTimerEnd, float delay = 0f, object data = null)
    {
        var timer = RequireTimer();
        timer.delayTimeMS = delay * 1000;
        timer.totalTimeMS = leftTime * 1000;
        timer.onTimerEnd = (t) => onTimerEnd();
        timer.loop = false;
        timer.data = data;
        timer.Start();
        return timer;
    }

    public GameTimer Invoke( float leftTime, TimeDelegate onTimerEnd, float delay = 0f, object data = null)
    {
        var timer = RequireTimer();
        timer.delayTimeMS = delay * 1000;
        timer.totalTimeMS = leftTime * 1000;
        timer.onTimerEnd = onTimerEnd;
        timer.loop = false;
        timer.data = data;
        timer.Start();
        return timer;
    }

    public GameTimer Repeat( float delay, float interval, float leftTime, bool loop = true, TimeDelegate onTimer = null, TimeDelegate onTimerEnd = null, object data = null)
    {
        var timer = RequireTimer();
        timer.delayTimeMS = delay * 1000;
        timer.intervalMS = interval * 1000;
        timer.totalTimeMS = leftTime * 1000;
        timer.onTimer = onTimer;
        timer.onTimerEnd = onTimerEnd;
        timer.loop = loop;
        timer.data = data;
        timer.Start();
        return timer;
    }

    public GameTimer RepeatNow(float delay, float interval, float leftTime, TimeDelegate onTimer = null, TimeDelegate onTimerEnd = null, object data = null)
    {
        throw new Exception();
    }
}

