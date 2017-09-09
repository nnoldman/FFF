/** This is an automatically generated class by FairyGUI. Please do not modify it. **/

using FairyGUI;
using FairyGUI.Utils;

namespace Basics
{
	public partial class WindowA : GComponent
	{
		public WindowFrame frame;

		public const string URL = "ui://9leh0eyfl6f473";

		public static WindowA CreateInstance()
		{
			return (WindowA)UIPackage.CreateObject("Basics","WindowA");
		}

		public WindowA()
		{
		}

		public override void ConstructFromXML(XML xml)
		{
			base.ConstructFromXML(xml);

			frame = (WindowFrame)this.GetChild("frame");
		}
	}
}