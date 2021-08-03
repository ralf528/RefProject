#ifndef __MYTYPE_H__
#define __MYTYPE_H__
//��������������������������������������������������������������������������������������������������������������
// �٦��� 2015.04, ���� ����ü �� ���� Ÿ��, Ackashic. ������
//��������������������������������������������������������������������������������������������������������������

typedef struct tagAni_Info
{
	E_ImageID RCID;

    //������ ���μ��� ũ��
    SIZE			aniSize;
    //������ ����
    int				frameCntX;
    int				frameCntY;
    //�ִϸ��̼� ���ǵ�
    int				frameSpeed;
    //���� ������
    int				nowFrame;
    int				nowFrameY;
    //< ����
    //������ ���� Ÿ��
    DWORD			lastTime;
    //�÷���
    bool			flag;
    bool			playAni;		//< ������ �����ӿ� �ӹ������ϴ� ���
    bool			loop;

}ANI_INFO, *LPANI_INFO;

enum E_AnimationType
{
    None = 0,
    Idle,
    Move,
    Attack,
    Die,
    BeHit,
	Dash,
    HitEff,
};

enum DIR
{
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT,
    DIR_UP
};


//��������������������������������������������������������������������������������������������������������������
// �٦��� 2015.04, ĳ���� �������ͽ�, Ackashic. ������
//��������������������������������������������������������������������������������������������������������������

enum ESTATUS_TYPE
{
	EStatus_None = -1,
	EStatus_Base = 0,
	EStatus_Skill,
	EStatus_Item,
};

//< �������ͽ�
typedef struct tagStatus
{
    //< �ų�
    unsigned int m_belief;
    //< ����
    unsigned int m_tribe;
    //< ����
    unsigned int m_job;

    //< �����̻�
    unsigned int m_condition;

}UNIT_STATUS;

//< ������
typedef struct tagDeley
{
    //< ������
    unsigned int m_deley;
    //< ī��Ʈ
    unsigned int m_lastTime;
}DELEY;


#endif