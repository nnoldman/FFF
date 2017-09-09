/** This is an automatically generated class by FairyGUI. Please do not modify it. **/

using FairyGUI;
using FairyGUI.Utils;

namespace Login
{
	public partial class RolePanel : GComponent
	{
		public GTextField name1;
		public GButton enterGame2;

		public const string URL = "ui://3aca1ugujce8n";

		public static RolePanel CreateInstance()
		{
			return (RolePanel)UIPackage.CreateObject("Login","RolePanel");
		}

		public RolePanel()
		{
		}

		public override void ConstructFromXML(XML xml)
		{
			base.ConstructFromXML(xml);

			name1 = (GTextField)this.GetChild("name1");
			enterGame2 = (GButton)this.GetChild("enterGame2");
		}
	}
}