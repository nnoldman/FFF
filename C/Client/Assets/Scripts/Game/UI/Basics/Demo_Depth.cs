/** This is an automatically generated class by FairyGUI. Please do not modify it. **/

using FairyGUI;
using FairyGUI.Utils;

namespace Basics
{
	public partial class Demo_Depth : GComponent
	{
		public GButton btn0;
		public GButton btn1;

		public const string URL = "ui://9leh0eyffou97q";

		public static Demo_Depth CreateInstance()
		{
			return (Demo_Depth)UIPackage.CreateObject("Basics","Demo_Depth");
		}

		public Demo_Depth()
		{
		}

		public override void ConstructFromXML(XML xml)
		{
			base.ConstructFromXML(xml);

			btn0 = (GButton)this.GetChild("btn0");
			btn1 = (GButton)this.GetChild("btn1");
		}
	}
}