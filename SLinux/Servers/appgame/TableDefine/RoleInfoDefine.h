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
        u32 functions[GameDefine::Function / sizeof(u32) / 8];//����
        int bagOpened;
        int bagCapicity;
    };

    /*
    ����
    */
    struct Property {
        int values[GameDefine::ProertyCount];
    };

    /*
    �ʼ�
    */
    struct Mail {
        int uuids[GameDefine::Mail];
    };

    /*
    ���е���
    */
    struct GameObjects {

    };

    /*
    ����
    */
    struct Env {
        //��ǰ��
        int trun;
        //���˶�
        int fitness;
        //������(exp)
        int energy;
        //������������(exp)
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
    struct Gene {
        //������
        int geneQuantity;
        //ͻ����
        int geneVariables;
    };

    /*
    ����
    */
    struct Group {
        ////��������
        //int correction;
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
    struct Member {
        //����
        int weight;
        //ʳ������
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
    struct Awareness {
        //�ڲ���ɻ����
        int innerElectrics;
    };

    /*
    ��̱��¼�
    */
    struct MileStone {
        int id;
        int time;
        Basic::CharBuffer<Default::EventName>  name;
    };

    /*
    �Ƽ�
    */
    struct Teachnology {
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
