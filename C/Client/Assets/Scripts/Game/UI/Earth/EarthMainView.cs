/** This is an automatically generated class by FairyGUI. Please do not modify it. **/

using FairyGUI;
using FairyGUI.Utils;

namespace Earth
{
	public partial class EarthMainView : GComponent
	{
		public GComponent frame_;
		public GList propertyList_;

		public const string URL = "ui://i7dv7mx1tx650";

		public static EarthMainView CreateInstance()
		{
			return (EarthMainView)UIPackage.CreateObject("Earth","EarthMainView");
		}

		public EarthMainView()
		{
		}

		public override void ConstructFromXML(XML xml)
		{
			base.ConstructFromXML(xml);

			frame_ = (GComponent)this.GetChild("frame_");
			propertyList_ = (GList)this.GetChild("propertyList_");
		}
	}
}