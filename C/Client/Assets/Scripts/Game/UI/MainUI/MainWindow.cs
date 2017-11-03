/** This is an automatically generated class by FairyGUI. Please do not modify it. **/

using FairyGUI;
using FairyGUI.Utils;

namespace MainUI
{
	public partial class MainWindow : GComponent
	{
		public GTextField name_;
		public GTextField time_;
		public GTextField period_;
		public GButton bm1_;
		public GButton bm2_;
		public GButton bm3_;
		public GButton bm4_;
		public GButton bm5_;

		public const string URL = "ui://mghxzakcshrc0";

		public static MainWindow CreateInstance()
		{
			return (MainWindow)UIPackage.CreateObject("MainUI","MainWindow");
		}

		public MainWindow()
		{
		}

		public override void ConstructFromXML(XML xml)
		{
			base.ConstructFromXML(xml);

			name_ = (GTextField)this.GetChild("name_");
			time_ = (GTextField)this.GetChild("time_");
			period_ = (GTextField)this.GetChild("period_");
			bm1_ = (GButton)this.GetChild("bm1_");
			bm2_ = (GButton)this.GetChild("bm2_");
			bm3_ = (GButton)this.GetChild("bm3_");
			bm4_ = (GButton)this.GetChild("bm4_");
			bm5_ = (GButton)this.GetChild("bm5_");
		}
	}
}