/** This is an automatically generated class by FairyGUI. Please do not modify it. **/

using FairyGUI;
using FairyGUI.Utils;

namespace Basics
{
	public partial class Dropdown2 : GComponent
	{
		public GList list;

		public const string URL = "ui://9leh0eyfzd9g47";

		public static Dropdown2 CreateInstance()
		{
			return (Dropdown2)UIPackage.CreateObject("Basics","Dropdown2");
		}

		public Dropdown2()
		{
		}

		public override void ConstructFromXML(XML xml)
		{
			base.ConstructFromXML(xml);

			list = (GList)this.GetChild("list");
		}
	}
}