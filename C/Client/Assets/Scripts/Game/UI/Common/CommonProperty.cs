/** This is an automatically generated class by FairyGUI. Please do not modify it. **/

using FairyGUI;
using FairyGUI.Utils;

namespace Common
{
	public partial class CommonProperty : GComponent
	{
		public GTextField name_;
		public GTextField value_;

		public const string URL = "ui://gx77j113gvbhg";

		public static CommonProperty CreateInstance()
		{
			return (CommonProperty)UIPackage.CreateObject("Common","CommonProperty");
		}

		public CommonProperty()
		{
		}

		public override void ConstructFromXML(XML xml)
		{
			base.ConstructFromXML(xml);

			name_ = (GTextField)this.GetChild("name_");
			value_ = (GTextField)this.GetChild("value_");
		}
	}
}