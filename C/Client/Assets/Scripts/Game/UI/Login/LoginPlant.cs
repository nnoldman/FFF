/** This is an automatically generated class by FairyGUI. Please do not modify it. **/

using FairyGUI;
using FairyGUI.Utils;

namespace Login
{
	public partial class LoginPlant : GComponent
	{
		public GTextInput user;
		public GTextInput psw;
		public GButton login;
		public GButton exit;

		public const string URL = "ui://3aca1ugukr711";

		public static LoginPlant CreateInstance()
		{
			return (LoginPlant)UIPackage.CreateObject("Login","LoginPlant");
		}

		public LoginPlant()
		{
		}

		public override void ConstructFromXML(XML xml)
		{
			base.ConstructFromXML(xml);

			user = (GTextInput)this.GetChild("user");
			psw = (GTextInput)this.GetChild("psw");
			login = (GButton)this.GetChild("login");
			exit = (GButton)this.GetChild("exit");
		}
	}
}