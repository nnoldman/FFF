using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

public delegate void TimeDelegate(GameTimer Timer);

public class GameTimer
{
    public delegate bool IsActive(object target);
    public static IsActive isTargetActive;

    public TimeDelegate onTimer
    {
        get;
        set;
    }
    public TimeDelegate onTimerEnd
    {
        get;
        set;
    }
    public bool loop
    {
        get;
        set;
    }
    public bool canPause = true;
    public bool useTimeScale = false;
    public object data;

    public float progress
    {
        get
        {
            return leftSeconds / totalSeconds;
        }
    }
    internal GameTimer()
    {
    }


    public void ClearDelegate()
    {
        onTimer = null;
        onTimerEnd = null;
    }
    public TimeSpan formatTime
    {
        get
        {
            return TimeSpan.FromSeconds(mTotalTime - mPassTime);
        }
    }

    public double totalTimeMS
    {
        get
        {
            return mTotalTime;
        }
        set
        {
            mTotalTime = value;
        }
    }
    public double delayTimeMS
    {
        get
        {
            return mDelayTime;
        }
        set
        {
            mDelayTime = value;
        }
    }
    public double intervalMS
    {
        get
        {
            return mInterval;
        }
        set
        {
            mInterval = value;
        }
    }

    public float totalSeconds
    {
        get
        {
            return (float)(mTotalTime * 0.001);
        }
    }
    public int passSecondsInt
    {
        get
        {
            return (int)Math.Ceiling(mPassTime > mTotalTime ? (float)(mTotalTime * 0.001) : (float)(mPassTime * 0.001));
        }
    }
    public float passSeconds
    {
        get
        {
            return mPassTime > mTotalTime ? (float)(mTotalTime * 0.001) : (float)(mPassTime * 0.001);
        }
        set
        {
            mPassTime = value * 1000;
        }
    }
    public float leftSeconds
    {
        get
        {
            return mTotalTime > mPassTime ? (float)((mTotalTime - mPassTime) * 0.001) : 0;
        }
    }
    public int leftSecondsInt
    {
        get
        {
            return mTotalTime > mPassTime ? (int)Math.Ceiling((mTotalTime - mPassTime) * 0.001) : 0;
        }
    }
    public int hour
    {
        get
        {
            return leftSecondsInt / 3600;
        }
    }
    public int minute
    {
        get
        {
            return leftSecondsInt / 60;
        }
    }
    public string stringHourMinSeconds
    {
        get
        {
            double left = leftSecondsInt;
            int h = hour;
            int m = (((int)left) % 3600) / 60;
            int s = ((int)left) % 60;
            return string.Format("{0:00}:{1:00}:{2:00}", h, m, s);
        }
    }
    public string stringMinSeconds
    {
        get
        {
            double left = leftSecondsInt;
            int m = minute;
            int s = ((int)left) % 60;
            return string.Format("{0:00}:{1:00}", m, s);
        }
    }

    public int id
    {
        get
        {
            return mID;
        }
        internal set
        {
            mID = value;
        }
    }

    public bool running
    {
        get
        {
            return mIsBegined && !mIsEnd;
        }
    }
    public bool begin
    {
        get
        {
            return mIsBegined;
        }
    }
    public bool end
    {
        get
        {
            return mIsEnd;
        }
    }
    public bool isGarbage
    {
        get
        {
            return mIsGarbage;
        }
    }

    private int mID = 0;
    private bool mIsBegined = false;
    private bool mIsEnd = false;
    private bool mPause = false;
    private bool mIsGarbage = false;

    private double mPauseTime = 0;
    private double mPassTime = 0;
    private double mTotalTime = 0;
    private double mDelayTime = 0;
    private double mInterval = 200;

    private int mFrameCount = 0;

    public void Stop(bool triggerEndCallback = false)
    {
        InnerSetEnd(triggerEndCallback);
    }

    void Reset()
    {
        mFrameCount = 0;
        mIsGarbage = false;
        mIsBegined = false;
        mIsEnd = false;
    }

    public void Start()
    {
        Reset();
        mIsBegined = true;
        if(mDelayTime == 0)
        {
            if (onTimer != null)
                onTimer(this);
        }
    }

    public void AdvanceTime(double deltaTime)
    {
        if (!mIsBegined || mIsEnd)
            return;

        if (mPause)
        {
            mPauseTime += deltaTime;
            return;
        }

        mPassTime += deltaTime;

        if (mPassTime < mDelayTime)
            return;

        int frame = (int)((mPassTime) / intervalMS);

        if (frame != mFrameCount)
        {
            if (onTimer != null)
            {
                if(isTargetActive == null || isTargetActive(onTimer.Target))
                    onTimer(this);
            }
            mFrameCount = frame;
        }

        if (mPassTime > mTotalTime && !loop)
        {
            InnerSetEnd(true);
            mPassTime = 0;
            this.Remove();
        }
    }

    void InnerSetEnd(bool triggerEvent)
    {
        mIsBegined = false;
        mIsEnd = true;
        if (triggerEvent && onTimerEnd != null)
            onTimerEnd(this);
        this.Remove();
    }

    public void Pause()
    {
        if (canPause)
            mPause = true;
    }
    public void Resume()
    {
        mPause = false;
    }

    void Remove()
    {
        mTotalTime = 0;
        mPassTime = 0;
        onTimer = null;
        onTimerEnd = null;
        mIsGarbage = true;
    }
}

