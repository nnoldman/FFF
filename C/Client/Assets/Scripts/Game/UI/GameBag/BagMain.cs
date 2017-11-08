/** This is an automatically generated class by FairyGUI. Please do not modify it. **/

using FairyGUI;
using FairyGUI.Utils;

namespace GameBag
{
	public partial class BagMain : GComponent
	{
		public Controller page;
		public GComponent frame_;
		public GList items_;
		public GList pages_;

		public const string URL = "ui://avih9elsszbr0";

		public static BagMain CreateInstance()
		{
			return (BagMain)UIPackage.CreateObject("GameBag","BagMain");
		}

		public BagMain()
		{
		}

		public override void ConstructFromXML(XML xml)
		{
			base.ConstructFromXML(xml);

			page = this.GetController("page");
			frame_ = (GComponent)this.GetChild("frame_");
			items_ = (GList)this.GetChild("items_");
			pages_ = (GList)this.GetChild("pages_");
		}
	}
}