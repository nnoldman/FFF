/** This is an automatically generated class by FairyGUI. Please do not modify it. **/

using FairyGUI;
using FairyGUI.Utils;

namespace Basics
{
	public partial class Demo_Button : GComponent
	{
		public Controller RadioGroup;
		public Controller tab;

		public const string URL = "ui://9leh0eyfrpmb1b";

		public static Demo_Button CreateInstance()
		{
			return (Demo_Button)UIPackage.CreateObject("Basics","Demo_Button");
		}

		public Demo_Button()
		{
		}

		public override void ConstructFromXML(XML xml)
		{
			base.ConstructFromXML(xml);

			RadioGroup = this.GetController("RadioGroup");
			tab = this.GetController("tab");
		}
	}
}