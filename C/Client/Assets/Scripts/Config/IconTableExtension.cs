using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
public partial class IconTable : TableManager<IconTableRecord>
{
    public override int MakeKey(IconTableRecord obj)
    {
        return obj.ID;
    }
}
