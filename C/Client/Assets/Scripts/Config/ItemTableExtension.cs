using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
public partial class ItemTable : TableManager<ItemTableRecord>
{
    public override int MakeKey(ItemTableRecord obj)
    {
        return obj.ID;
    }
}
