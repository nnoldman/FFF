using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
namespace TestTimer
{
public class Timer
{
    const string DLLName = "../../../../Debug/Timers.dll";
    public delegate void _ImportOnTimerEnd(IntPtr timer);
    public delegate void OnTimerEnd(Timer timer);
    [DllImport(DLLName)]
    extern static IntPtr timer_wait(Int64 microseconds, _ImportOnTimerEnd onTimerEnd);
    [DllImport(DLLName)]
    extern static Int64 timer_getLeftTime(IntPtr timer);
    [DllImport(DLLName)]
    extern static void timer_tick();
    private Timer()
    {
        onEndCallback_ = new _ImportOnTimerEnd(_OnTimerEnd);
    }

    public static Timer Wait(Int64 microseconds, OnTimerEnd onEnd)
    {
        Timer ret = new Timer();
        ret.onTimerEnd_ = onEnd;
        ret.timer_ = timer_wait(microseconds, ret.onEndCallback_);
        return ret;
    }

    public static void Tick()
    {
        timer_tick();
    }

    public void _OnTimerEnd(IntPtr timer)
    {
        if (onTimerEnd_ != null)
            onTimerEnd_(this);
        timer_ = IntPtr.Zero;
    }

    public Int64 leftTime
    {
        get
        {
            return timer_getLeftTime(timer_);
        }
    }

    public void Dispose()
    {
    }

    private IntPtr timer_;
    private _ImportOnTimerEnd onEndCallback_;
    private OnTimerEnd onTimerEnd_;
}
}
