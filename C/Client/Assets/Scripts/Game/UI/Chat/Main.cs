/** This is an automatically generated class by FairyGUI. Please do not modify it. **/

using FairyGUI;
using FairyGUI.Utils;

namespace Chat
{
	public partial class Main : GButton
	{
		public GList list_;
		public GComponent channel_;
		public GTextInput input_;
		public GButton emotion_;
		public GButton send_;

		public const string URL = "ui://u7ozu3y5rab3e";

		public static Main CreateInstance()
		{
			return (Main)UIPackage.CreateObject("Chat","Main");
		}

		public Main()
		{
		}

		public override void ConstructFromXML(XML xml)
		{
			base.ConstructFromXML(xml);

			list_ = (GList)this.GetChild("list_");
			channel_ = (GComponent)this.GetChild("channel_");
			input_ = (GTextInput)this.GetChild("input_");
			emotion_ = (GButton)this.GetChild("emotion_");
			send_ = (GButton)this.GetChild("send_");
		}
	}
}