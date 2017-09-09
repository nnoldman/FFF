/** This is an automatically generated class by FairyGUI. Please do not modify it. **/

using FairyGUI;
using FairyGUI.Utils;

namespace Bag
{
	public partial class BagWin : GComponent
	{
		public Controller page;
		public WindowFrame frame;
		public GList list;

		public const string URL = "ui://rbw1tv9tkcy10";

		public static BagWin CreateInstance()
		{
			return (BagWin)UIPackage.CreateObject("Bag","BagWin");
		}

		public BagWin()
		{
		}

		public override void ConstructFromXML(XML xml)
		{
			base.ConstructFromXML(xml);

			page = this.GetControllerAt(0);
			frame = (WindowFrame)this.GetChildAt(0);
			list = (GList)this.GetChildAt(1);
		}
	}
}