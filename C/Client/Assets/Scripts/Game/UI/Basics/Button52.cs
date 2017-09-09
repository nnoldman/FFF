/** This is an automatically generated class by FairyGUI. Please do not modify it. **/

using FairyGUI;
using FairyGUI.Utils;

namespace Basics
{
	public partial class Button52 : GButton
	{
		public Controller grayed;
		public GImage bg;

		public const string URL = "ui://9leh0eyfdyz47i";

		public static Button52 CreateInstance()
		{
			return (Button52)UIPackage.CreateObject("Basics","Button52");
		}

		public Button52()
		{
		}

		public override void ConstructFromXML(XML xml)
		{
			base.ConstructFromXML(xml);

			grayed = this.GetController("grayed");
			bg = (GImage)this.GetChild("bg");
		}
	}
}