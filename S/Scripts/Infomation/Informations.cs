using System.Collections;
using System.Collections.Generic;
using System.IO;
using System;
using Data;

public class KingInfo
{
    public int active = 1;
    public int generalIdx;
    public List<int> cities;
    public List<int> generals;
}

public class CityInfo
{
    public int king;
    public int prefect;
    public int population;
    public int money;
    public int reservist;
    public int reservistMax;
    public int defense;
    public List<int> objects;
    public List<int> generals;
    public List<int> prisons;

    public int soldiersNum
    {

        get
        {

            int s = 0;
            for (int i = 0; i < generals.Count; i++)
            {

                int gIdx = (int)generals[i];
                s += Informations.Instance.GetGeneralInfo(gIdx).soldierCur;
            }

            return s;
        }
    }
}



public class SoliderInfo
{
    public static int DEGREE_COUNT=4;
    public static int LEVEL_LIMIT = 8;

    public int id = 0;
    public SoliderType type = 0;
    public int star = 1;
    public int general = 0;
    public int level = 0;
    public string name;
    public bool die = false;
    public UInt64 exp = 0;
    public int attack
    {
        get
        {
            return propData.attack;
        }
    }
    public int defence
    {
        get
        {
            return propData.defence;
        }
    }
    public float attackRange
    {
        get
        {
            return propData.attackRange;
        }
    }
    public int health
    {
        get
        {
            return propData.hp;
        }
    }
    public int speed
    {
        get
        {
            return propData.speed;
        }
    }
    public int leaderCondtion
    {
        get
        {
            return armyData.updegreeInfos[star - 1].leadCondtion;
        }
    }
    public string texture
    {
        get
        {
            return armyData.updegreeInfos[star - 1].texture;
        }
    }
    public bool HasGeneral()
    {
        return general != 0;
    }
    public void GenerateByRandom()
    {
    }
    public string GetPrefab(bool left)
    {
        GameData.ArmyData armdata = GameData.ArmyData.Get(type);
        if (armdata != null)
            return armdata.updegreeInfos[star - 1].getPrefabString(left);
        return null;
    }
    public GameData.ArmyData armyData
    {
        get
        {
            return GameData.ArmyData.Get(type);
        }
    }
    public GameData.Property propData
    {
        get
        {
            return GameData.SoldierPropertyData.GetProperty(type, star, level);
        }
    }
}
public enum SkillState
{
    Unknown,        ///未满足条件
    CanLearn,       ///满足条件
    Learned,        ///已学成
    Count,
}
public class SkillStateData
{
    public int skillID=0;
    public int level = 1;
    public SkillState state=SkillState.Unknown;

    public GameData.SkillData data
    {
        get
        {
            return GameData.SkillData.Get(skillID);
        }
    }
    public SkillProperty prop
    {
        get
        {
            return data.props[level - 1];
        }
    }
}

public class GeneralInfo
{
    public static int SOLDIER_LIMIT = 16;
    public static int LEVEL_LIMIT = 10;
    public static int EQUIP_COUNT_LIMIT = 4;
    public static int ASVISER_COUNT_LIMIT = 3;
    public int id;
    public int active = 1;
    public int king = -1;
    public int city = -1;
    public int prisonerIdx = -1;
    public int loyalty = 100;
    public int[] magic = new int[4];
    public int job;
    //public int equipment;
    public int strength;
    public int intellect;
    public UInt64 experience;
    public int level;
    public int health;
    public int healthCur;
    public int manaMax;
    public int manaCur;
    public int soldierMax;
    public int soldierCur;
    public int knightMax;
    public int knightCur;
    public int arms;
    public int armsCur;
    public int formation;
    public int formationCur;
    public int escape;

    public int force;           ///战力
    public int captain;         ///统帅

    public List<int> soliderInfo = new List<int>();
    public List<SoliderInfo> soliders = new List<SoliderInfo>();
    public List<SkillStateData> skills = new List<SkillStateData>();
    public t_ObjectProto[] equips = new t_ObjectProto[EQUIP_COUNT_LIMIT];

    public GameData.PropertyOfGeneral propData
    {
        get
        {
            return gamedata.baseinfos[level-1];
        }
    }
    public GameData.GeneralData gamedata
    {
        get
        {
            return GameData.GeneralData.Get(id);
        }
    }

    public void SetStateToBegin()
    {
        healthCur = propData.hp;
    }

    public SkillStateData adviserSkill
    {
        get
        {
            if (!gamedata.adviser)
                return null;
            SkillStateData askill = new SkillStateData();
            askill.level = 1;
            askill.skillID = 1003;
            askill.state = SkillState.Learned;
            return askill;
        }
    }

    public bool main
    {
        get
        {
            return id == Informations.Instance.mine.mainGeneral;
        }
    }
}

public class EquipmentInfo
{
    public int type;
    public int data;
}

public class ArmyInfo
{
    public static int SETTING_GENERAL_MAX=3;
    public int king = -1;
    public int cityFrom = -1;
    public int cityTo = -1;
    public int commander = -1;
    public int money = 0;

    public int state;
    public int direction;
    public bool isFlipped;
    public Vector3 pos;
    public float timeTick;

    //public List<int> generals = new List<int>();
    public List<int> prisons = new List<int>();


    public DList<int> advisers = new DList<int>();
    public DList<int> selectedGenerals = new DList<int>();

    public DInt selectedAdviser = new DInt();
    public DInt mainGeneral = new DInt();
    public DInt scanGeneral = new DInt();
    public DInt scanCapture = new DInt(-1);

    public int maxGeneralNum = 3;
    public DMap<int, SoliderInfo> soliders = new DMap<int, SoliderInfo>();
    public int updegreeingSoldier = 0;
}

public class SimpleArmyInfo
{
    public List<GeneralInfo> selectedGenerals = new List<GeneralInfo>();
    public List<GeneralInfo> selectedAdvisers = new List<GeneralInfo>();
}


public class Informations
{
    private KingInfo[] kings;
    private CityInfo[] cities;
    private EquipmentInfo[] equipments;

    public DList<GeneralInfo> generals = new DList<GeneralInfo>();
    public ItemMgr ItemMgr = new ItemMgr();

    public StatVip statVip;
    public StatSign statSign;

    public StatRole statRole;

    public StatChat statChat;

    public StatDugeonChapterMap statDugeonChapterMap;
    public StatDugeonChapterMap statDugeonChapterMapElite; 

    public int kingNum = 18;
    public int cityNum = 48;
    public int generalNum = 255;
    public int magicNum = 50;
    public int equipmentNum = 31;
    public int armsNum = 11;
    public int formationNum = 7;
    public int jobsNum = 50;

    public int[] modKingNum = new int[] { 14, 18, 8, 8, 5 };

    public List<ArmyInfo> armys;
    public ArmyInfo mine;
    public DMap<int,StatCapture> captures;
    public Dictionary<int, StatDungeon> dungeons;

    private static Informations instance;
    public static Informations Instance
    {
        get
        {
            if (instance == null)
            {
                instance = new Informations();
            }
            return instance;
        }
    }

    private bool InitMaterial()
    {
        return true;
    }
    public static void Reset()
    {
        instance = null;
    }
    public Informations()
    {
        armys = new List<ArmyInfo>();
        mine = new ArmyInfo();
        captures = new DMap<int, StatCapture>();
        dungeons = new Dictionary<int, StatDungeon>();
        statVip = new StatVip();
        statSign = new StatSign();
        statRole = new StatRole();
        statRole.RandomGenerate();
        statChat = new StatChat();
        statDugeonChapterMap = new StatDugeonChapterMap();
        statDugeonChapterMapElite = new StatDugeonChapterMap();
        InitArmy();
        InitDefaultGeneralsInfo();
    }
    public StatDugeonChapterMap GetStatDugeonChapterMap(bool elite)
    {
        return elite ? statDugeonChapterMapElite : statDugeonChapterMap;
    }
    private void InitArmy()
    {
        int idx = 0;
        foreach(var d in GameData.GeneralData.dataMap)
        {
            StatCapture stat = new StatCapture();
            stat.id = d.Key;
            //stat.lv = UnityEngine.Random.Range(1, 11);
            //stat.power = UnityEngine.Random.Range(300, 800);
            //stat.presentLeftTime = (uint)UnityEngine.Random.Range(0, 3600);
            //stat.intimacy = UnityEngine.Random.Range(0, 101);
            captures.Add(idx, stat);
            idx++;
        }

        //for (int i = 0; i < (int)SoliderType.Count; ++i)
        //{
        //    for (int j = 1; j <= (int)SoliderInfo.DEGREE_COUNT; ++j)
        //    {
        //        SoliderInfo info = new SoliderInfo();
        //        info.id = i * SoliderInfo.DEGREE_COUNT + j - 1;
        //        info.level = UnityEngine.Random.Range(1, 8);
        //        info.star = UnityEngine.Random.Range(1, SoliderInfo.DEGREE_COUNT + 1);
        //        info.type = (SoliderType)i;
        //        info.die = false;
        //        info.name = Localization.Get(info.armyData.alias) + j.ToString();
        //        mine.soliders.Add(info.id, info);
        //    }
        //}
    }

    public EquipmentInfo GetEquipmentInfo(int idx)
    {
        if (idx < 0 || idx >= equipmentNum) return null;
        if (equipments == null)
        {
            InitEquipmentInfo();
        }

        return equipments[idx];
    }

    public KingInfo GetKingInfo(int idx)
    {
        if (idx < 0 || idx >= kingNum + 1)
        {
            return null;
        }

        if (kings == null)
        {
            //InitDefaultKingsInfo();
            //InitKingInfo();
            //MODLoadController.Instance.LoadMOD(Controller.MODSelect);
        }

        return kings[idx];
    }

    public void SetKingInfo(int idx, KingInfo kInfo)
    {

        if (kings == null)
        {
            kings = new KingInfo[kingNum + 1];
        }

        kings[idx] = kInfo;
    }

    public CityInfo GetCityInfo(int idx)
    {
        if (idx < 0 || idx >= cityNum)
            return null;

        if (cities == null)
        {
            //InitDefaultCitiesInfo();
            //InitCityPrefect();
            //InitCityInfo();
            //MODLoadController.Instance.LoadMOD(Controller.MODSelect);
        }

        return cities[idx];
    }

    public void SetCityInfo(int idx, CityInfo cInfo)
    {

        if (cities == null)
        {
            cities = new CityInfo[cityNum];
        }

        cities[idx] = cInfo;
    }

    public GeneralInfo GetGeneralInfo(int idx)
    {
        int index = generals.FindIndex((info) => info.id == idx);
        return generals[index];
    }
    public void UpdateGeneralSoldierInfo(int idx)
    {
        GeneralInfo info = GetGeneralInfo(idx);
        if (info != null)
        {
            info.soliders.Clear();
            foreach(var soldier in Informations.Instance.mine.soliders)
            {
                if (soldier.Value.general == idx)
                {
                    info.soliders.Add(soldier.Value);
                    info.soldierCur++;
                }
            }
        }
    }
    public void SetGeneralInfo(int idx, GeneralInfo gInfo)
    {

        //if (generals == null)
        //{
        //    generals = new GeneralInfo[generalNum];
        //}

        //generals[idx] = gInfo;


    }

    public void InitKingInfo()
    {
        InitKingCities();
        InitKingGenerals();
    }

    public void InitCityInfo()
    {
        //test
        InitCityObjects();
        InitCityGenerals();
    }

    public void InitGeneralInfo()
    {
        for (int i = 0; i < generalNum; i++)
        {
            generals[i].job = generals[i].magic[0];
        }

        for (int m = 0; m < generalNum; m++)
        {
            int arms = generals[m].arms;
            int i = 0;
            while (i < armsNum && (arms & (1 << i)) == 0) i++;
            generals[m].armsCur = 1 << i;
        }

        for (int m = 0; m < generalNum; m++)
        {
            int formation = generals[m].formation;
            int i = formationNum;
            while (i >= 0 && (formation & (1 << i)) == 0) i--;

            generals[m].formationCur = 1 << i;
        }
    }

    /// <summary>
    /// Inits the king cities.
    /// </summary>

    private void InitKingCities()
    {
        for (int idx = 0; idx < kingNum + 1; idx++)
        {

            KingInfo kInfo = GetKingInfo(idx);
            kInfo.cities = new List<int>();

            for (int i = 0; i < cityNum; i++)
            {
                CityInfo cInfo = GetCityInfo(i);

                if (cInfo.king == idx)
                {
                    kInfo.cities.Add(i);
                }
            }
        }
    }

    private void InitKingGenerals()
    {
        for (int idx = 0; idx < kingNum + 1; idx++)
        {

            KingInfo kInfo = GetKingInfo(idx);
            kInfo.generals = new List<int>();

            for (int i = generalNum - 1; i >= 0; i--)
            {
                GeneralInfo gInfo = GetGeneralInfo(i);

                if (gInfo.king == idx && gInfo.prisonerIdx == -1)
                {
                    kInfo.generals.Add(i);
                }
            }
        }
    }

    /// <summary>
    /// Inits the city prefect.
    /// </summary>

    public void InitCityPrefect()
    {

        for (int idx = 0; idx < cityNum; idx++)
        {

            CityInfo cInfo = GetCityInfo(idx);

            if (cInfo.king == -1) continue;

            KingInfo kInfo = GetKingInfo(cInfo.king);
            if (GetGeneralInfo(kInfo.generalIdx).city == idx)
            {
                cInfo.prefect = kInfo.generalIdx;
                continue;
            }

            int gIdx = -1;
            for (int i = generalNum - 1; i >= 0; i--)
            {
                GeneralInfo gInfo = GetGeneralInfo(i);

                if (gInfo.city == idx && gInfo.king == cInfo.king && gInfo.prisonerIdx == -1)
                {
                    if (gIdx == -1)
                    {
                        gIdx = i;
                    }
                    else
                    {
                        if (GetGeneralInfo(gIdx).strength < gInfo.strength)
                        {
                            gIdx = i;
                        }
                    }
                }
            }

            cInfo.prefect = gIdx;
        }
    }

    private void InitCityObjects()
    {

        for (int idx = 0; idx < cityNum; idx++)
        {

            CityInfo cInfo = GetCityInfo(idx);
            if (cInfo.objects == null)
            {
                cInfo.objects = new List<int>();
            }
            //test
            /*
            for (int i=0; i<5; i++) {
                int obj = 0;
				
                if (Random.Range(0, 100) < 33) { 
                    obj = 1 << 16;
                    obj += Random.Range(0, equipmentNum);
                } else if (Random.Range(0, 100) < 66) {
                    obj = 2 << 16;
                    obj += 1 << Random.Range(0, armsNum);
                } else {
                    obj = 3 << 16;
                    obj += 1 << Random.Range(0, formationNum);
                }
				
                cInfo.objects.Add(obj);
            }*/
        }
    }

    private void InitCityGenerals()
    {

        for (int idx = 0; idx < cityNum; idx++)
        {

            CityInfo cInfo = GetCityInfo(idx);

            cInfo.generals = new List<int>();
            cInfo.prisons = new List<int>();

            for (int i = generalNum - 1; i >= 0; i--)
            {
                GeneralInfo gInfo = GetGeneralInfo(i);

                if (gInfo.city == idx)
                {
                    if (cInfo.king == -1)
                    {
                        gInfo.king = -1;
                        gInfo.city = -1;
                    }
                    else if (gInfo.king == cInfo.king && gInfo.prisonerIdx == -1)
                    {
                        cInfo.generals.Add(i);
                    }
                    else if (gInfo.prisonerIdx != -1)
                    {
                        gInfo.prisonerIdx = cInfo.king;
                        cInfo.prisons.Add(i);
                    }
                    else
                    {

                        gInfo.king = -1;
                        gInfo.city = -1;
                    }
                }
            }
        }
    }


    /// <summary>
    /// Inits the default kings info.
    /// </summary>

    private void InitDefaultKingsInfo()
    {
        if (kings == null)
        {
            kings = new KingInfo[kingNum + 1];
            for (int i = 0; i < kingNum + 1; i++)
            {
                kings[i] = new KingInfo();
            }
        }

        kings[0].generalIdx = 98;
        kings[1].generalIdx = 134;
        kings[2].generalIdx = 59;
        kings[3].generalIdx = 121;
        kings[4].generalIdx = 71;
        kings[5].generalIdx = 72;
        kings[6].generalIdx = 3;
        kings[7].generalIdx = 156;
        kings[8].generalIdx = 7;
        kings[9].generalIdx = 189;
        kings[10].generalIdx = 79;
        kings[11].generalIdx = 110;
        kings[12].generalIdx = 6;
        kings[13].generalIdx = 132;
        kings[14].generalIdx = 137;
        kings[15].generalIdx = 167;
        kings[16].generalIdx = 172;
        kings[17].generalIdx = 133;
    }

    private void InitDefaultCitiesInfo()
    {

        if (cities == null)
        {
            cities = new CityInfo[cityNum];
            for (int i = 0; i < cityNum; i++)
            {
                cities[i] = new CityInfo();
            }
        }

        cities[0X00].king = -1;
        cities[0X00].population = 77000;
        cities[0X00].money = 2827;
        cities[0X00].reservistMax = 140;
        cities[0X00].reservist = 0;
        cities[0X00].defense = 369;

        cities[0X01].king = 6;
        cities[0X01].population = 90000;
        cities[0X01].money = 2925;
        cities[0X01].reservistMax = 146;
        cities[0X01].reservist = 0;
        cities[0X01].defense = 252;

        cities[0X02].king = 4;
        cities[0X02].population = 172739;
        cities[0X02].money = 3472;
        cities[0X02].reservistMax = 179;
        cities[0X02].reservist = 0;
        cities[0X02].defense = 321;

        cities[0X03].king = -1;
        cities[0X03].population = 88000;
        cities[0X03].money = 2910;
        cities[0X03].reservistMax = 145;
        cities[0X03].reservist = 0;
        cities[0X03].defense = 300;

        cities[0X04].king = 4;
        cities[0X04].population = 355340;
        cities[0X04].money = 4822;
        cities[0X04].reservistMax = 252;
        cities[0X04].reservist = 0;
        cities[0X04].defense = 439;

        cities[0X05].king = 1;
        cities[0X05].population = 330000;
        cities[0X05].money = 4725;
        cities[0X05].reservistMax = 242;
        cities[0X05].reservist = 0;
        cities[0X05].defense = 365;

        cities[0X06].king = 7;
        cities[0X06].population = 214229;
        cities[0X06].money = 3795;
        cities[0X06].reservistMax = 195;
        cities[0X06].reservist = 0;
        cities[0X06].defense = 312;

        cities[0X07].king = 8;
        cities[0X07].population = 129646;
        cities[0X07].money = 3135;
        cities[0X07].reservistMax = 161;
        cities[0X07].reservist = 0;
        cities[0X07].defense = 320;

        cities[0X08].king = 9;
        cities[0X08].population = 167000;
        cities[0X08].money = 3502;
        cities[0X08].reservistMax = 176;
        cities[0X08].reservist = 0;
        cities[0X08].defense = 227;

        cities[0X09].king = 0;
        cities[0X09].population = 221000;
        cities[0X09].money = 3907;
        cities[0X09].reservistMax = 198;
        cities[0X09].reservist = 0;
        cities[0X09].defense = 206;

        cities[0X0A].king = 3;
        cities[0X0A].population = 425000;
        cities[0X0A].money = 5437;
        cities[0X0A].reservistMax = 280;
        cities[0X0A].reservist = 0;
        cities[0X0A].defense = 500;

        cities[0X0B].king = 3;
        cities[0X0B].population = 142000;
        cities[0X0B].money = 3315;
        cities[0X0B].reservistMax = 166;
        cities[0X0B].reservist = 0;
        cities[0X0B].defense = 232;

        cities[0X0C].king = 3;
        cities[0X0C].population = 308093;
        cities[0X0C].money = 4492;
        cities[0X0C].reservistMax = 233;
        cities[0X0C].reservist = 0;
        cities[0X0C].defense = 513;

        cities[0X0D].king = -1;
        cities[0X0D].population = 89000;
        cities[0X0D].money = 2917;
        cities[0X0D].reservistMax = 145;
        cities[0X0D].reservist = 0;
        cities[0X0D].defense = 245;

        cities[0X0E].king = -1;
        cities[0X0E].population = 121000;
        cities[0X0E].money = 3157;
        cities[0X0E].reservistMax = 158;
        cities[0X0E].reservist = 0;
        cities[0X0E].defense = 373;

        cities[0X0F].king = 10;
        cities[0X0F].population = 160000;
        cities[0X0F].money = 3450;
        cities[0X0F].reservistMax = 174;
        cities[0X0F].reservist = 0;
        cities[0X0F].defense = 515;

        cities[0X10].king = 11;
        cities[0X10].population = 167000;
        cities[0X10].money = 3502;
        cities[0X10].reservistMax = 176;
        cities[0X10].reservist = 0;
        cities[0X10].defense = 140;

        cities[0X11].king = 11;
        cities[0X11].population = 188000;
        cities[0X11].money = 3660;
        cities[0X11].reservistMax = 185;
        cities[0X11].reservist = 0;
        cities[0X11].defense = 106;

        cities[0X12].king = -1;
        cities[0X12].population = 321000;
        cities[0X12].money = 4657;
        cities[0X12].reservistMax = 238;
        cities[0X12].reservist = 0;
        cities[0X12].defense = 429;

        cities[0X13].king = 12;
        cities[0X13].population = 233000;
        cities[0X13].money = 3997;
        cities[0X13].reservistMax = 206;
        cities[0X13].reservist = 0;
        cities[0X13].defense = 305;

        cities[0X14].king = -1;
        cities[0X14].population = 251000;
        cities[0X14].money = 4132;
        cities[0X14].reservistMax = 210;
        cities[0X14].reservist = 0;
        cities[0X14].defense = 137;

        cities[0X15].king = 5;
        cities[0X15].population = 325000;
        cities[0X15].money = 4687;
        cities[0X15].reservistMax = 240;
        cities[0X15].reservist = 0;
        cities[0X15].defense = 317;

        cities[0X16].king = -1;
        cities[0X16].population = 213000;
        cities[0X16].money = 3847;
        cities[0X16].reservistMax = 195;
        cities[0X16].reservist = 0;
        cities[0X16].defense = 207;

        cities[0X17].king = 13;
        cities[0X17].population = 370566;
        cities[0X17].money = 4950;
        cities[0X17].reservistMax = 258;
        cities[0X17].reservist = 0;
        cities[0X17].defense = 345;

        cities[0X18].king = -1;
        cities[0X18].population = 254000;
        cities[0X18].money = 4155;
        cities[0X18].reservistMax = 211;
        cities[0X18].reservist = 0;
        cities[0X18].defense = 214;

        cities[0X19].king = 13;
        cities[0X19].population = 132000;
        cities[0X19].money = 3240;
        cities[0X19].reservistMax = 162;
        cities[0X19].reservist = 0;
        cities[0X19].defense = 236;

        cities[0X1A].king = 13;
        cities[0X1A].population = 233000;
        cities[0X1A].money = 3997;
        cities[0X1A].reservistMax = 203;
        cities[0X1A].reservist = 0;
        cities[0X1A].defense = 294;

        cities[0X1B].king = -1;
        cities[0X1B].population = 109000;
        cities[0X1B].money = 3067;
        cities[0X1B].reservistMax = 153;
        cities[0X1B].reservist = 0;
        cities[0X1B].defense = 175;

        cities[0X1C].king = 2;
        cities[0X1C].population = 224000;
        cities[0X1C].money = 3930;
        cities[0X1C].reservistMax = 199;
        cities[0X1C].reservist = 0;
        cities[0X1C].defense = 473;

        cities[0X1D].king = -1;
        cities[0X1D].population = 174000;
        cities[0X1D].money = 3555;
        cities[0X1D].reservistMax = 179;
        cities[0X1D].reservist = 0;
        cities[0X1D].defense = 121;

        cities[0X1E].king = -1;
        cities[0X1E].population = 225000;
        cities[0X1E].money = 3937;
        cities[0X1E].reservistMax = 200;
        cities[0X1E].reservist = 0;
        cities[0X1E].defense = 132;

        cities[0X1F].king = 14;
        cities[0X1F].population = 154000;
        cities[0X1F].money = 3405;
        cities[0X1F].reservistMax = 171;
        cities[0X1F].reservist = 0;
        cities[0X1F].defense = 182;

        cities[0X20].king = 14;
        cities[0X20].population = 290000;
        cities[0X20].money = 4425;
        cities[0X20].reservistMax = 226;
        cities[0X20].reservist = 0;
        cities[0X20].defense = 420;

        cities[0X21].king = 15;
        cities[0X21].population = 232000;
        cities[0X21].money = 3990;
        cities[0X21].reservistMax = 202;
        cities[0X21].reservist = 0;
        cities[0X21].defense = 336;

        cities[0X22].king = 16;
        cities[0X22].population = 139000;
        cities[0X22].money = 3292;
        cities[0X22].reservistMax = 165;
        cities[0X22].reservist = 0;
        cities[0X22].defense = 160;

        cities[0X23].king = -1;
        cities[0X23].population = 170000;
        cities[0X23].money = 3525;
        cities[0X23].reservistMax = 178;
        cities[0X23].reservist = 0;
        cities[0X23].defense = 203;

        cities[0X24].king = -1;
        cities[0X24].population = 213000;
        cities[0X24].money = 3847;
        cities[0X24].reservistMax = 195;
        cities[0X24].reservist = 0;
        cities[0X24].defense = 233;

        cities[0X25].king = -1;
        cities[0X25].population = 181000;
        cities[0X25].money = 3607;
        cities[0X25].reservistMax = 182;
        cities[0X25].reservist = 0;
        cities[0X25].defense = 502;

        cities[0X26].king = -1;
        cities[0X26].population = 115000;
        cities[0X26].money = 3112;
        cities[0X26].reservistMax = 156;
        cities[0X26].reservist = 0;
        cities[0X26].defense = 211;

        cities[0X27].king = 17;
        cities[0X27].population = 235000;
        cities[0X27].money = 4012;
        cities[0X27].reservistMax = 204;
        cities[0X27].reservist = 0;
        cities[0X27].defense = 306;

        cities[0X28].king = 17;
        cities[0X28].population = 308000;
        cities[0X28].money = 4560;
        cities[0X28].reservistMax = 233;
        cities[0X28].reservist = 0;
        cities[0X28].defense = 284;

        cities[0X29].king = -1;
        cities[0X29].population = 236000;
        cities[0X29].money = 4020;
        cities[0X29].reservistMax = 204;
        cities[0X29].reservist = 0;
        cities[0X29].defense = 268;

        cities[0X2A].king = 17;
        cities[0X2A].population = 211000;
        cities[0X2A].money = 3832;
        cities[0X2A].reservistMax = 194;
        cities[0X2A].reservist = 0;
        cities[0X2A].defense = 162;

        cities[0X2B].king = -1;
        cities[0X2B].population = 176000;
        cities[0X2B].money = 3570;
        cities[0X2B].reservistMax = 180;
        cities[0X2B].reservist = 0;
        cities[0X2B].defense = 193;

        cities[0X2C].king = -1;
        cities[0X2C].population = 303000;
        cities[0X2C].money = 4522;
        cities[0X2C].reservistMax = 231;
        cities[0X2C].reservist = 0;
        cities[0X2C].defense = 375;

        cities[0X2D].king = -1;
        cities[0X2D].population = 149000;
        cities[0X2D].money = 3367;
        cities[0X2D].reservistMax = 169;
        cities[0X2D].reservist = 0;
        cities[0X2D].defense = 112;

        cities[0X2E].king = -1;
        cities[0X2E].population = 166000;
        cities[0X2E].money = 3495;
        cities[0X2E].reservistMax = 176;
        cities[0X2E].reservist = 0;
        cities[0X2E].defense = 244;

        cities[0X2F].king = -1;
        cities[0X2F].population = 62000;
        cities[0X2F].money = 2715;
        cities[0X2F].reservistMax = 134;
        cities[0X2F].reservist = 0;
        cities[0X2F].defense = 108;
    }

    private void InitDefaultGeneralsInfo()
    {
        int[] skillids = new int[] { 1001, 1002, 1003, 1004, 1201, 1202, 1203 };

        int sid = 0;

        foreach (var genData in GameData.GeneralData.dataMap)
        {
            int gIdx = genData.Key;
            GeneralInfo info = new GeneralInfo();

            info.id = gIdx;


            //info.level = UnityEngine.Random.Range(1, GeneralInfo.LEVEL_LIMIT + 1);
            info.healthCur = info.propData.hp;
            generals.Add(info);

            foreach (int skid in skillids)
            {
                SkillStateData data = new SkillStateData();
                data.skillID = skid;
                //data.state = (SkillState)(UnityEngine.Random.Range(0, (int)SkillState.Count));
                info.skills.Add(data);
            }

            if (info.gamedata.adviser && mine.advisers.Count < GeneralInfo.ASVISER_COUNT_LIMIT)
            {
                mine.advisers.Add(info.id);
            }

            uint[] equiplist = new uint[1115 - 1109 + 1] { 1109, 1110, 1111, 1112, 1113, 1114, 1115 };
            List<uint> elist = new List<uint>();
            elist.AddRange(equiplist);
            for (int i = 0; i < GeneralInfo.EQUIP_COUNT_LIMIT; ++i)
            {
                t_ObjectProto equip = new t_ObjectProto();
                equip.lv = 1;
                //int idex = UnityEngine.Random.Range(0, elist.Count);
                //equip.dwObjectID = equiplist[idex];
                //elist.Remove(equip.dwObjectID);
                //info.equips[i] = equip;
            }

            sid += GeneralInfo.SOLDIER_LIMIT;
        }
    }

    private void InitEquipmentInfo()
    {
        if (equipments == null)
        {
            equipments = new EquipmentInfo[equipmentNum];
            for (int i = 0; i < equipmentNum; i++)
            {
                equipments[i] = new EquipmentInfo();
            }
        }

        equipments[0].type = 0; // zhi li
        equipments[0].data = 10;

        equipments[1].type = 0;
        equipments[1].data = 9;

        equipments[2].type = 0;
        equipments[2].data = 9;

        equipments[3].type = 0;
        equipments[3].data = 8;

        equipments[4].type = 0;
        equipments[4].data = 7;

        equipments[5].type = 1; // ji li
        equipments[5].data = 10;

        equipments[6].type = 2; // sheng ming
        equipments[6].data = 10;

        equipments[7].type = 1;
        equipments[7].data = 10;

        equipments[8].type = 3; // wu li
        equipments[8].data = 10;

        equipments[9].type = 3;
        equipments[9].data = 10;

        equipments[10].type = 3;
        equipments[10].data = 9;

        equipments[11].type = 3;
        equipments[11].data = 9;

        equipments[12].type = 3;
        equipments[12].data = 8;

        equipments[13].type = 3;
        equipments[13].data = 5;

        equipments[14].type = 3;
        equipments[14].data = 7;

        equipments[15].type = 3;
        equipments[15].data = 7;

        equipments[16].type = 3;
        equipments[16].data = 6;

        equipments[17].type = 3;
        equipments[17].data = 6;

        equipments[18].type = 3;
        equipments[18].data = 6;

        equipments[19].type = 3;
        equipments[19].data = 4;

        equipments[20].type = 3;
        equipments[20].data = 4;

        equipments[21].type = 3;
        equipments[21].data = 4;

        equipments[22].type = 3;
        equipments[22].data = 4;

        equipments[23].type = 3;
        equipments[23].data = 4;

        equipments[24].type = 3;
        equipments[24].data = 2;

        equipments[25].type = 3;
        equipments[25].data = 2;

        equipments[26].type = 3;
        equipments[26].data = 2;

        equipments[27].type = 4;
        equipments[27].data = 3;

        equipments[28].type = 4;
        equipments[28].data = 4;

        equipments[29].type = 4;
        equipments[29].data = 2;

        equipments[30].type = 4;
        equipments[30].data = 1;
    }

    public int[,] generalBody = new int[255, 2]{
		{7, 5},		//丁奉
		{2, 12},		//于禁
		{2, 15},		//兀突骨
		{5, 8},		//公孙瓒
		{7, 5},		//卞喜
		{7, 15},		//太史慈
		{7, 6},		//孔岫
		{0, 11},		//孔融
		{3, 12},		//文钦
		{4, 0},		//文聘
		{6, 3},		//文鸯
		{7, 11},		//文丑
		{4, 6},		//牛金
		{9, 5},		//王允
		{0, 14},		//王双
		{9, 16},		//司马炎
		{3, 3},		//司马昭
		{4, 6},		//司马师
		{9, 16},		//司马懿
		{0, 15},		//甘宁
		{7, 4},		//田丰
		{6, 6},		//伊籍
		{1, 15},		//全琮
		{7, 11},		//忙牙长
		{9, 11},		//朱桓
		{1, 16},		//朵思大王
		{7, 12},		//吴兰
		{1, 12},		//吴懿
		{0, 9},		//吕布
		{1, 16},		//吕蒙
		{9, 5},		//宋宪
		{6, 6},		//李典
		{1, 0},		//李恢
		{6, 14},		//李儒
		{0, 4},		//李严
		{5, 6},		//李傕
		{0, 2},		//步鹭
		{3, 16},		//沙摩诃
		{9, 3},		//车胄
		{0, 6},		//邢道荣
		{7, 4},		//典韦
		{4, 5},		//周仓
		{1, 4},		//周泰
		{4, 16},		//周瑜
		{6, 0},		//孟达
		{4, 0},		//孟优
		{7, 12},		//孟获
		{5, 14},		//法正
		{3, 16},		//沮授
		{8, 4},		//金环三结
		{1, 11},		//阿会喃
		{4, 12},		//姜维
		{7, 12},		//纪灵
		{5, 6},		//胡车儿
		{8, 4},		//凌统
		{4, 5},		//凌操
		{7, 15},		//夏侯惇
		{1, 14},		//夏侯渊
		{6, 5},		//夏侯霸
		{4, 3},		//孙坚
		{3, 14},		//孙策
		{6, 14},		//孙权
		{0, 0},		//孙翊
		{1, 2},		//徐晃
		{3, 16},		//徐庶
		{1, 7},		//徐盛
		{7, 6},		//徐质
		{1, 1},		//祝融夫人
		{9, 16},		//荀攸
		{9, 16},		//荀彧
		{4, 1},		//袁尚
		{2, 7},		//袁绍
		{2, 1},		//袁术
		{6, 5},		//袁熙
		{0, 3},		//袁谭
		{6, 15},		//郝昭
		{4, 4},		//马良
		{3, 0},		//马岱
		{4, 12},		//马超
		{0, 4},		//马腾
		{9, 0},		//马谡
		{9, 12},		//高顺
		{3, 5},		//高览
		{4, 15},		//张任
		{3, 12},		//张松
		{8, 16},		//张虎
		{7, 12},		//张昭
		{9, 8},		//张苞
		{6, 15},		//张郃
		{7, 10},		//张飞
		{2, 7},		//张鲁
		{5, 11},		//张辽
		{6, 14},		//张纮
		{4, 14},		//曹仁
		{8, 5},		//曹芳
		{3, 14},		//曹爽
		{9, 7},		//曹植
		{9, 8},		//曹彰
		{2, 3},		//曹操
		{7, 11},		//曹睿
		{4, 12},		//许褚
		{9, 5},		//逢纪
		{9, 16},		//郭嘉
		{6, 12},		//郭图
		{0, 7},		//郭汜
		{7, 15},		//陈宫
		{8, 7},		//陈琳
		{6, 8},		//陈群
		{1, 11},		//陆抗
		{2, 16},		//陆逊
		{0, 16},		//陶谦
		{2, 1},		//程昱
		{7, 0},		//程普
		{4, 14},		//华雄
		{6, 7},		//华歆
		{6, 7},		//黄忠
		{8, 7},		//黄祖
		{5, 2},		//黄盖
		{1, 15},		//黄权
		{7, 0},		//杨修
		{7, 4},		//董允
		{7, 15},		//董卓
		{5, 14},		//董荼那
		{2, 2},		//贾充
		{9, 16},		//贾诩
		{3, 6},		//廖化
		{7, 5},		//满宠
		{5, 8},		//赵统
		{5, 5},		//赵云
		{5, 0},		//赵广
		{9, 2},		//蒯良
		{3, 8},		//蒯越
		{3, 2},		//刘表
		{2, 0},		//刘焉
		{2, 2},		//刘备
		{6, 0},		//刘晔
		{9, 0},		//刘禅
		{1, 0},		//刘繇
		{9, 6},		//樊稠
		{4, 5},		//乐进
		{7, 5},		//潘璋
		{6, 7},		//蒋济
		{5, 1},		//蒋琬
		{6, 14},		//蔡邕
		{9, 6},		//蔡瑁
		{9, 16},		//诸葛亮
		{8, 0},		//诸葛恪
		{8, 8},		//诸葛瑾
		{9, 16},		//鲁肃
		{1, 1},		//邓艾
		{4, 12},		//邓忠
		{2, 15},		//邓芝
		{0, 11},		//卢植
		{2, 1},		//阎圃
		{3, 12},		//钟会
		{3, 3},		//韩当
		{2, 11},		//韩馥
		{4, 14},		//颜良
		{7, 15},		//魏延
		{1, 14},		//魏续
		{1, 12},		//庞统
		{7, 11},		//庞德
		{2, 0},		//谯周
		{5, 5},		//关平
		{4, 13},		//关羽
		{6, 12},		//关索
		{0, 11},		//关兴
		{2, 8},		//严白虎
		{8, 15},		//严纲
		{9, 6},		//严舆
		{7, 15},		//严颜
		{8, 1},		//公孙越
		{5, 15},		//王朗
		{4, 0},		//朱治
		{7, 6},		//辛评
		{9, 14},		//武安国
		{4, 0},		//皇甫嵩
		{1, 6},		//孙乾
		{3, 4},		//祖茂
		{7, 15},		//马玩
		{5, 2},		//高沛
		{8, 5},		//张勋
		{3, 1},		//张济
		{8, 6},		//曹洪
		{0, 3},		//梁兴
		{9, 3},		//陈武
		{4, 7},		//陈登
		{8, 16},		//陈横
		{0, 3},		//乔玄
		{5, 3},		//乔瑁
		{1, 0},		//关凤
		{9, 11},		//杨怀
		{0, 0},		//虞翻
		{4, 11},		//邹靖
		{3, 16},		//雷铜
		{4, 6},		//雷薄
		{9, 12},		//刘璋
		{2, 0},		//潘凤
		{9, 0},		//霍峻
		{8, 1},		//糜竺
		{5, 4},		//糜芳
		{1, 3},		//韩嵩
		{5, 11},		//简雍
		{0, 0},		//阚泽
		{3, 14},		//曹丕
		{1, 0},		//貂蝉
		{1, 0},		//孙尚香
		{1, 11},		//何进
		{6, 12},		//张英
		{0, 2},		//丁原
		{2, 3},		//张角
		{6, 0},		//张梁
		{1, 7},		//张宝
		{4, 16},		//程远志
		{0, 15},		//邓茂
		{5, 0},		//管亥
		{1, 0},		//赵弘
		{4, 0},		//韩忠
		{5, 2},		//龚都
		{4, 11},		//何仪
		{9, 3},		//龚景
		{1, 11},		//曹真
		{6, 3},		//刘封
		{9, 16},		//董承
		{1, 0},		//董袭
		{9, 5},		//张闿
		{8, 3},		//张翼
		{0, 4},		//张嶷
		{7, 3},		//彻里吉
		{2, 2},		//臧霸
		{0, 14},		//徐荣
		{9, 16},		//夏侯恩
		{2, 1},		//淳于琼
		{6, 0},		//曹休
		{0, 8},		//曹纯
		{2, 0},		//孙韶
		{1, 1},		//金旋
		{9, 0},		//公孙康
		{6, 0},		//向朗
		{1, 0},		//吕范
		{4, 12},		//李异
		{2, 5},		//夏侯尚
		{5, 16},		//于吉
		{0, 16},		//左慈
		{1, 6},		//孙静
		{2, 3},		//桓范
		{1, 11},		//费祎
		{4, 12},		//轲比能
		{0, 14},		//董旻
		{9, 2},		//刘琦
		{0, 15},		//刘琮
		{1, 6},		//蒋钦
		{5, 4},		//苏飞
		{9, 8},		//谭雄
		{4, 11},		//顾雍
		
	};
}