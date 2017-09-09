/** This is an automatically generated class by FairyGUI. Please do not modify it. **/

using FairyGUI;
using FairyGUI.Utils;

namespace Basics
{
	public partial class Button5 : GButton
	{
		public GImage bg;

		public const string URL = "ui://9leh0eyfrpmb13";

		public static Button5 CreateInstance()
		{
			return (Button5)UIPackage.CreateObject("Basics","Button5");
		}

		public Button5()
		{
		}

		public override void ConstructFromXML(XML xml)
		{
			base.ConstructFromXML(xml);

			bg = (GImage)this.GetChild("bg");
		}
	}
}