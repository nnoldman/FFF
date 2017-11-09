/** This is an automatically generated class by FairyGUI. Please do not modify it. **/

using FairyGUI;
using FairyGUI.Utils;

namespace Common
{
	public partial class CommonTitle : GComponent
	{
		public Controller page;

		public const string URL = "ui://gx77j113rab3t";

		public static CommonTitle CreateInstance()
		{
			return (CommonTitle)UIPackage.CreateObject("Common","CommonTitle");
		}

		public CommonTitle()
		{
		}

		public override void ConstructFromXML(XML xml)
		{
			base.ConstructFromXML(xml);

			page = this.GetController("page");
		}
	}
}