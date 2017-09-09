/** This is an automatically generated class by FairyGUI. Please do not modify it. **/

using FairyGUI;
using FairyGUI.Utils;

namespace Login
{
	public partial class SelectServer : GComponent
	{
		public GList serverList;
		public GTextField currentServer;
		public GButton enterGame;

		public const string URL = "ui://3aca1ugufl9n2";

		public static SelectServer CreateInstance()
		{
			return (SelectServer)UIPackage.CreateObject("Login","SelectServer");
		}

		public SelectServer()
		{
		}

		public override void ConstructFromXML(XML xml)
		{
			base.ConstructFromXML(xml);

			serverList = (GList)this.GetChild("serverList");
			currentServer = (GTextField)this.GetChild("currentServer");
			enterGame = (GButton)this.GetChild("enterGame");
		}
	}
}