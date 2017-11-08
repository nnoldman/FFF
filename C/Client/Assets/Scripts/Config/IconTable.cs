using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

//
//@author: Administrator
//@time:2017/11/6 14:42:34
//工具生成，请勿修改！
//

public class IconTableRecord
{
	public int ID;
	public int TextureID;
	public string Explain;
	public int PX;
	public int PY;
	public int Width;
	public int Height;
	public int FrameCount;
	public int FPL;
}

public partial class IconTable : TableManager<IconTableRecord>
{
    public static IconTable Instance;
    public override string TableName()
    {
        return "IconTable.txt";
    }
}


