/** This is an automatically generated class by FairyGUI. Please do not modify it. **/

using FairyGUI;
using FairyGUI.Utils;

namespace Bag
{
	public partial class Main : GComponent
	{
		public GButton bagBtn;

		public const string URL = "ui://rbw1tv9tfvaib";

		public static Main CreateInstance()
		{
			return (Main)UIPackage.CreateObject("Bag","Main");
		}

		public Main()
		{
		}

		public override void ConstructFromXML(XML xml)
		{
			base.ConstructFromXML(xml);

			bagBtn = (GButton)this.GetChildAt(0);
		}
	}
}