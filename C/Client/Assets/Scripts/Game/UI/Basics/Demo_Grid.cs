/** This is an automatically generated class by FairyGUI. Please do not modify it. **/

using FairyGUI;
using FairyGUI.Utils;

namespace Basics
{
	public partial class Demo_Grid : GComponent
	{
		public GList list1;
		public GList list2;

		public const string URL = "ui://9leh0eyfc2z47l";

		public static Demo_Grid CreateInstance()
		{
			return (Demo_Grid)UIPackage.CreateObject("Basics","Demo_Grid");
		}

		public Demo_Grid()
		{
		}

		public override void ConstructFromXML(XML xml)
		{
			base.ConstructFromXML(xml);

			list1 = (GList)this.GetChild("list1");
			list2 = (GList)this.GetChild("list2");
		}
	}
}