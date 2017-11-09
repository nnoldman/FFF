/** This is an automatically generated class by FairyGUI. Please do not modify it. **/

using FairyGUI;
using FairyGUI.Utils;

namespace CommonBack
{
	public partial class WindowTemplete : GComponent
	{
		public GButton contentarea_;
		public GTextField title_;
		public GButton close_;

		public const string URL = "ui://iw1uby6xtx650";

		public static WindowTemplete CreateInstance()
		{
			return (WindowTemplete)UIPackage.CreateObject("CommonBack","WindowTemplete");
		}

		public WindowTemplete()
		{
		}

		public override void ConstructFromXML(XML xml)
		{
			base.ConstructFromXML(xml);

			contentarea_ = (GButton)this.GetChild("contentarea_");
			title_ = (GTextField)this.GetChild("title_");
			close_ = (GButton)this.GetChild("close_");
		}
	}
}