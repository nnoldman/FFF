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
    public string GetContent(int id)
    {
        var recourd = Get(id);
        if (recourd != null)
            return recourd.text;
        return string.Empty;
    }

    public string GetPropertyName(RolePropertyID id)
    {
        return GetContent((int)id + 20);
    }
}
