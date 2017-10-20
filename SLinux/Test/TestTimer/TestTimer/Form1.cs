using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TestTimer
{
public partial class Form1 : Form
{
    public Form1()
    {
        InitializeComponent();
        this.SetStyle(ControlStyles.DoubleBuffer | ControlStyles.UserPaint | ControlStyles.AllPaintingInWmPaint, true);
        this.UpdateStyles();
    }

    private Timer timer_;

    private void button1_Click(object sender, EventArgs e)
    {
        timer_ = Timer.Wait(5000, OnTimerEnd);
    }

    void OnTimerEnd(Timer timer)
    {
    }

    protected override void OnPaint(PaintEventArgs e)
    {
        base.OnPaint(e);
        Timer.Tick();
        if (timer_ != null)
        {
            TimeSpan span = TimeSpan.FromMilliseconds(timer_.leftTime);
            this.labelTimer.Text = span.ToString();
        }
        this.Refresh();
    }
}
}
