/** This is an automatically generated class by FairyGUI. Please do not modify it. **/

using FairyGUI;
using FairyGUI.Utils;

namespace Common
{
	public partial class CommonProgressBar : GProgressBar
	{
		public GTextField name_;

		public const string URL = "ui://gx77j113uriyh";

		public static CommonProgressBar CreateInstance()
		{
			return (CommonProgressBar)UIPackage.CreateObject("Common","CommonProgressBar");
		}

		public CommonProgressBar()
		{
		}

		public override void ConstructFromXML(XML xml)
		{
			base.ConstructFromXML(xml);

			name_ = (GTextField)this.GetChild("name_");
		}
	}
}