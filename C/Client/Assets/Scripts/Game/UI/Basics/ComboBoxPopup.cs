/** This is an automatically generated class by FairyGUI. Please do not modify it. **/

using FairyGUI;
using FairyGUI.Utils;

namespace Basics
{
	public partial class ComboBoxPopup : GComponent
	{
		public GList list;

		public const string URL = "ui://9leh0eyfrt103y";

		public static ComboBoxPopup CreateInstance()
		{
			return (ComboBoxPopup)UIPackage.CreateObject("Basics","ComboBoxPopup");
		}

		public ComboBoxPopup()
		{
		}

		public override void ConstructFromXML(XML xml)
		{
			base.ConstructFromXML(xml);

			list = (GList)this.GetChild("list");
		}
	}
}