/** This is an automatically generated class by FairyGUI. Please do not modify it. **/

using FairyGUI;
using FairyGUI.Utils;

namespace Basics
{
	public partial class Dropdown : GComboBox
	{
		public GButton button;

		public const string URL = "ui://9leh0eyfzd9g41";

		public static Dropdown CreateInstance()
		{
			return (Dropdown)UIPackage.CreateObject("Basics","Dropdown");
		}

		public Dropdown()
		{
		}

		public override void ConstructFromXML(XML xml)
		{
			base.ConstructFromXML(xml);

			button = (GButton)this.GetChild("button");
		}
	}
}