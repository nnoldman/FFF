using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GameData
{
    public class ChargeData:GameData<ChargeData>
    {
        static public readonly string fileName = "xml/Charge";

        public string price;
        public int icon;
        public int count;
        public int gift;

        public string titleString
        {
            get
            {
                return count.ToString()+LanguageData.MoneyString;
            }
        }
        public string descString
        {
            get
            {
                return Localization.Get(4)+ gift.ToString() + LanguageData.MoneyString;
            }
        }
        public string texture
        {
            get
            {
                return IconData.Get(icon).texture;
            }
        }

        public string priceString
        {
            get
            {
                return price + LanguageData.RMBString;
            }
        }
    }
}
