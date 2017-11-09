/** This is an automatically generated class by FairyGUI. Please do not modify it. **/

using FairyGUI;

namespace Common
{
	public class CommonBinder
	{
		public static void BindAll()
		{
			UIObjectFactory.SetPackageItemExtension(CommonProperty.URL, typeof(CommonProperty));
			UIObjectFactory.SetPackageItemExtension(CommonTitle.URL, typeof(CommonTitle));
			UIObjectFactory.SetPackageItemExtension(CommonProgressBar.URL, typeof(CommonProgressBar));
		}
	}
}