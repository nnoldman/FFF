/** This is an automatically generated class by FairyGUI. Please do not modify it. **/

using FairyGUI;
using FairyGUI.Utils;

namespace MessageBox
{
	public partial class MessageBox : GComponent
	{
		public GTextField content_;
		public GButton cancel_;
		public GButton ok_;

		public const string URL = "ui://aet6e809szbr0";

		public static MessageBox CreateInstance()
		{
			return (MessageBox)UIPackage.CreateObject("MessageBox","MessageBox");
		}

		public MessageBox()
		{
		}

		public override void ConstructFromXML(XML xml)
		{
			base.ConstructFromXML(xml);

			content_ = (GTextField)this.GetChild("content_");
			cancel_ = (GButton)this.GetChild("cancel_");
			ok_ = (GButton)this.GetChild("ok_");
		}
	}
}