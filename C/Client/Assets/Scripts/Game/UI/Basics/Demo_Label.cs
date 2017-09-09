/** This is an automatically generated class by FairyGUI. Please do not modify it. **/

using FairyGUI;
using FairyGUI.Utils;

namespace Basics
{
	public partial class Demo_Label : GComponent
	{
		public WindowFrame frame;

		public const string URL = "ui://9leh0eyfw42o3j";

		public static Demo_Label CreateInstance()
		{
			return (Demo_Label)UIPackage.CreateObject("Basics","Demo_Label");
		}

		public Demo_Label()
		{
		}

		public override void ConstructFromXML(XML xml)
		{
			base.ConstructFromXML(xml);

			frame = (WindowFrame)this.GetChild("frame");
		}
	}
}