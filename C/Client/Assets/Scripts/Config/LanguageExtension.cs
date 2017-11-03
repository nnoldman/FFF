using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
public partial class Language : TableManager<LanguageRecord>
{
    public override int MakeKey(LanguageRecord obj)
    {
        return obj.id;
    }
}
