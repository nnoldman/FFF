/** This is an automatically generated class by FairyGUI. Please do not modify it. **/

using FairyGUI;
using FairyGUI.Utils;

namespace Basics
{
	public partial class WindowFrameB : GLabel
	{
		public GGraph dragArea;
		public GButton closeButton;

		public const string URL = "ui://9leh0eyfniii7d";

		public static WindowFrameB CreateInstance()
		{
			return (WindowFrameB)UIPackage.CreateObject("Basics","WindowFrameB");
		}

		public WindowFrameB()
		{
		}

		public override void ConstructFromXML(XML xml)
		{
			base.ConstructFromXML(xml);

			dragArea = (GGraph)this.GetChild("dragArea");
			closeButton = (GButton)this.GetChild("closeButton");
		}
	}
}