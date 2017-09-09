/** This is an automatically generated class by FairyGUI. Please do not modify it. **/

using FairyGUI;
using FairyGUI.Utils;

namespace Basics
{
	public partial class Demo_Controller : GComponent
	{
		public Controller c1;
		public Controller c2;
		public GButton switchBtn;

		public const string URL = "ui://9leh0eyfwa8u2v";

		public static Demo_Controller CreateInstance()
		{
			return (Demo_Controller)UIPackage.CreateObject("Basics","Demo_Controller");
		}

		public Demo_Controller()
		{
		}

		public override void ConstructFromXML(XML xml)
		{
			base.ConstructFromXML(xml);

			c1 = this.GetController("c1");
			c2 = this.GetController("c2");
			switchBtn = (GButton)this.GetChild("switchBtn");
		}
	}
}