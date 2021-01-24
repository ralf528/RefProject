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
    bool			playAni;
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

//< �������ͽ�
typedef struct tagStates
{
    //< �ų�
    unsigned int m_belief;
    //< ����
    unsigned int m_tribe;
    //< ����
    unsigned int m_job;

    //< �ִ� ü��
    unsigned int m_maxHP;
    //< ���� ü��
    unsigned int m_nowHP;
    //< �ִ� ����
    unsigned int m_maxMP;
    //< ���� ����
    unsigned int m_nowMP;

    //< ��
    unsigned int m_str;
    //< ��
    unsigned int m_agl;
    //< ��
    unsigned int m_int;

    //< �̵��ӵ�
    float m_moveSpeed;

    //< �����̻�
    unsigned int m_condition;

}STATES;

//< ������
typedef struct tagDeley
{
    //< ������
    unsigned int m_deley;
    //< ī��Ʈ
    unsigned int m_lastTime;
}DELEY;


#endif