#pragma once
#include "GameDefine.pb.h"
#include "CharBuffer.h"
#include "Default.h"
namespace RoleStat {
    struct Base {
        Basic::CharBuffer<Default::NameSize> name;
        int vip;
        int level;
        int sex;
        int job;
        Basic::CharBuffer<Default::TimeSize> borntime;
        u32 functions[GameDefine::Function / sizeof(u32) / 8];//功能
        int bagOpened;
        int bagCapicity;
    };

    /*
    属性
    */
    struct Property {
        int values[GameDefine::ProertyCount];
    };

    /*
    邮件
    */
    struct Mail {
        int uuids[GameDefine::Mail];
    };

    /*
    所有道具
    */
    struct GameObjects {

    };

    /*
    环境
    */
    struct Env {
        //当前纪
        int trun;
        //适宜度
        int fitness;
        //总能量(exp)
        int energy;
        //升级所需能量(exp)
        int nextEnergy;
        //太阳强度
        int sunIntensity;
        //地壳总量
        int earthCrustQuantity;
        //火山活动量
        int volcanoTimes;
        //地壳运动量
        int earthCrustTimes;
        //地壳运动强度
        int earthCrustEffects;
        //大气量
        int airQuantity;
        //水蒸气
        int vapour;
        //氧含量
        int o2Percent;
        //地表温度
        int earthTemperature;
        //雷电量
        int thunderTimes;
        //海水PH
        int seaPH;
        //植被总量
        int botany;
    };

    /*
    内因
    */
    struct Gene {
        //基因量
        int geneQuantity;
        //突变子
        int geneVariables;
    };

    /*
    部落
    */
    struct Group {
        ////纠错能力
        //int correction;
        //部落成员数量
        int count;
        //部落分工量
        int divsion;
        //部落智慧
        int iq;
        //部落攻击能力
        int attack;
        //部落防守能力
        int defence;
        //附属族群
        int childGroup[GameDefine::Capcity::ChildGroup];
    };

    /*
    成员
    */
    struct Member {
        //体重
        int weight;
        //食物需求
        int food;
        //脑容量
        int brainQuantity;
        //神经元数量
        int neureQuantity;
        //脑部耗氧量
        int brainCostO2;
        //眼睛数量
        int eyeQuantity;
        //耳朵数量
        int earQuantity;
        //鼻子
        int noseQuantity;
        //免疫能力
        int immuneCapacity;
        //淋巴数量
        int lymphQuantity;
        //肌肉强度
        int muscleStrength;
        //骨骼强度
        int boneStrength;
        //繁殖能力
        int breedCapcity;
        //是否有甲壳，会影响行动力
        char hasShell;
    };

    /*
    意识
    */
    struct Awareness {
        //内部电荷活动总量
        int innerElectrics;
    };

    /*
    里程碑事件
    */
    struct MileStone {
        int id;
        int time;
        Basic::CharBuffer<Default::EventName>  name;
    };

    /*
    科技
    */
    struct Teachnology {
        //生物
        int biology;
        //数学
        int math;
        //哲学
        int philosophy;
        //经济学
        int economics;
        //物理学
        int physics;
        //社会学
        int sociology;
    };
}
