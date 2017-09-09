/** This is an automatically generated class by FairyGUI. Please do not modify it. **/

using FairyGUI;
using FairyGUI.Utils;

namespace Login
{
	public partial class ServerItem : GButton
	{
		public GTextField name_;

		public const string URL = "ui://3aca1ugufl9n3";

		public static ServerItem CreateInstance()
		{
			return (ServerItem)UIPackage.CreateObject("Login","ServerItem");
		}

		public ServerItem()
		{
		}

		public override void ConstructFromXML(XML xml)
		{
			base.ConstructFromXML(xml);

			name_ = (GTextField)this.GetChild("name_");
		}
	}
}