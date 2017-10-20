namespace TestTimer
{
partial class Form1
{
    /// <summary>
    /// 必需的设计器变量。
    /// </summary>
    private System.ComponentModel.IContainer components = null;

    /// <summary>
    /// 清理所有正在使用的资源。
    /// </summary>
    /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
    protected override void Dispose(bool disposing)
    {
        if (disposing && (components != null))
        {
            components.Dispose();
        }
        base.Dispose(disposing);
    }

    #region Windows 窗体设计器生成的代码

    /// <summary>
    /// 设计器支持所需的方法 - 不要修改
    /// 使用代码编辑器修改此方法的内容。
    /// </summary>
    private void InitializeComponent()
    {
        this.labelTimer = new System.Windows.Forms.Label();
        this.button1 = new System.Windows.Forms.Button();
        this.SuspendLayout();
        //
        // labelTimer
        //
        this.labelTimer.AutoSize = true;
        this.labelTimer.Location = new System.Drawing.Point(300, 44);
        this.labelTimer.Name = "labelTimer";
        this.labelTimer.Size = new System.Drawing.Size(41, 12);
        this.labelTimer.TabIndex = 0;
        this.labelTimer.Text = "label1";
        //
        // button1
        //
        this.button1.Location = new System.Drawing.Point(34, 30);
        this.button1.Name = "button1";
        this.button1.Size = new System.Drawing.Size(189, 40);
        this.button1.TabIndex = 1;
        this.button1.Text = "button1";
        this.button1.UseVisualStyleBackColor = true;
        this.button1.Click += new System.EventHandler(this.button1_Click);
        //
        // Form1
        //
        this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
        this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
        this.ClientSize = new System.Drawing.Size(850, 411);
        this.Controls.Add(this.button1);
        this.Controls.Add(this.labelTimer);
        this.Name = "Form1";
        this.Text = "Form1";
        this.ResumeLayout(false);
        this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.Label labelTimer;
    private System.Windows.Forms.Button button1;
}
}

