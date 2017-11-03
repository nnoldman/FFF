/** This is an automatically generated class by FairyGUI. Please do not modify it. **/

using FairyGUI;
using FairyGUI.Utils;

namespace MainUI
{
	public partial class TV : GComponent
	{
		public GTextField content_;

		public const string URL = "ui://mghxzakcspkj4";

		public static TV CreateInstance()
		{
			return (TV)UIPackage.CreateObject("MainUI","TV");
		}

		public TV()
		{
		}

		public override void ConstructFromXML(XML xml)
		{
			base.ConstructFromXML(xml);

			content_ = (GTextField)this.GetChild("content_");
		}
	}
}