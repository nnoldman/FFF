#pragma once
#include "GameDefine.pb.h"
namespace RoleStat
{
    struct Base
    {
        CharBuffer<Default::NameSize> name;
        int vip;
        int level;
        int sex;
        int job;
        CharBuffer<Default::TimeSize> borntime;
    };
    /*
    ����
    */
    struct Bag
    {
        int id;
        int openedQuantity;
        int capcity;
    };

    /*
    װ��
    */
    struct Equip
    {
        int uuids[GameDefine::Equip];
    };

    /*
    �ֿ�
    */
    struct Store
    {
        int uuids[GameDefine::Store];
    };

    /*
    �ʼ�
    */
    struct Mail
    {
        int uuids[GameDefine::Mail];
    };

    /*
    ����
    */
    struct Function
    {
        u32 uuids[GameDefine::Function / sizeof(u32) / 8];
    };

    /*
    ����
    */
    struct Env
    {
        //��ǰ��
        int trun;
        //������(exp)
        int energy;
        int nextEnergy;
        //̫��ǿ��
        int sunIntensity;
        //�ؿ�����
        int earthCrustQuantity;
        //��ɽ���
        int volcanoTimes;
        //�ؿ��˶���
        int earthCrustTimes;
        //�ؿ��˶�ǿ��
        int earthCrustEffects;
        //������
        int airQuantity;
        //ˮ����
        int vapour;
        //������
        int o2Percent;
        //�ر��¶�
        int earthTemperature;
        //�׵���
        int thunderTimes;
        //��ˮPH
        int seaPH;

        //ֲ������
        int botany;
    };

    /*
    ����
    */
    struct Gene
    {
        //������
        int geneQuantity;
        //ͻ����
        int geneVariables;
    };

    /*
    ����
    */
    struct Group
    {
        //��������
        int correction;
        //�����Ա����
        int count;
        //����ֹ���
        int divsion;
        //�����ǻ�
        int iq;
        //���乥������
        int attack;
        //�����������
        int defence;
        //������Ⱥ
        int childGroup[GameDefine::Capcity::ChildGroup];
    };

    /*
    ��Ա
    */
    struct Member
    {
        //����
        int weight;
        //ʵ������
        int food;
        //������
        int brainQuantity;
        //��Ԫ����
        int neureQuantity;
        //�Բ�������
        int brainCostO2;
        //�۾�����
        int eyeQuantity;
        //��������
        int earQuantity;
        //����
        int noseQuantity;
        //��������
        int immuneCapacity;
        //�ܰ�����
        int lymphQuantity;
        //����ǿ��
        int muscleStrength;
        //����ǿ��
        int boneStrength;
        //��ֳ����
        int breedCapcity;
        //�Ƿ��м׿ǣ���Ӱ���ж���
        char hasShell;
    };

    /*
    ��ʶ
    */
    struct Awareness
    {
        //�ڲ���ɻ����
        int innerElectrics;
    };

    /*
    ��̱��¼�
    */
    struct MileStone
    {
        int id;
        int time;
        CharBuffer<Default::EventName>  name;
    };

    /*
    �Ƽ�
    */
    struct Teachnology
    {
        //����
        int biology;
        //��ѧ
        int math;
        //��ѧ
        int philosophy;
        //����ѧ
        int economics;
        //����ѧ
        int physics;
        //���ѧ
        int sociology;
    };
}
