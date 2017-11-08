using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

//
//@author: Administrator
//@time:2017/11/6 16:24:22
//工具生成，请勿修改！
//

public class ItemTableRecord
{
	public int ID;
	public string Name;
	public int Level;
	public int Type;
	public int MaxNum;
	public int Quality;
	public int AutoSell;
	public int Use;
	public int BuyPrice;
	public int GoldPrice;
	public int GongDe;
	public int Recovery;
	public string Desc;
	public string Legend;
	public int Icon;
	public int MinAttack;
	public int MaxAttack;
	public int MinDefence;
	public int MaxDefence;
	public int MinWAttack;
	public int MaxWAttack;
	public int MinMAttack;
	public int MaxMAttack;
	public int MinGAttack;
	public int MaxGAttack;
	public int MinPAttack;
	public int MaxPAttack;
	public int MinDodge;
	public int MaxDodge;
	public int MinBang;
	public int MaxBang;
	public int MinASpeed;
	public int MaxASpeed;
	public int MinMSpeed;
	public int MaxMSpeed;
	public int MinAntiMine;
	public int MaxAntiMine;
	public int Body;
	public int Soul;
	public int UseLimit;
}

public partial class ItemTable : TableManager<ItemTableRecord>
{
    public static ItemTable Instance;
    public override string TableName()
    {
        return "ItemTable.txt";
    }
}


