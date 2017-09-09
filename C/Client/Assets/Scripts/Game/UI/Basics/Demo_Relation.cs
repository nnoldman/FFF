/** This is an automatically generated class by FairyGUI. Please do not modify it. **/

using FairyGUI;
using FairyGUI.Utils;

namespace Basics
{
	public partial class Demo_Relation : GComponent
	{
		public Controller c1;

		public const string URL = "ui://9leh0eyfwa8u2x";

		public static Demo_Relation CreateInstance()
		{
			return (Demo_Relation)UIPackage.CreateObject("Basics","Demo_Relation");
		}

		public Demo_Relation()
		{
		}

		public override void ConstructFromXML(XML xml)
		{
			base.ConstructFromXML(xml);

			c1 = this.GetController("c1");
		}
	}
}