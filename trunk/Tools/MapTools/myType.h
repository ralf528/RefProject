#ifndef __MYTYPE_H__
#define __MYTYPE_H__
//��������������������������������������������������������������������������������������������������������������
// �٦��� 2015.04, ���� ����ü �� ���� Ÿ��, Ackashic. ������
//��������������������������������������������������������������������������������������������������������������

typedef struct tagAniInfo
{
	//< �ִϸ��̼� ���� ����,����ũ��
	SIZE	aniSize;
	//< �ִϸ��̼� ���ΰ���
	int		frameCntX;
	//< �ִϸ��̼� ���ΰ���
	int		frameCntY;
	//< �ִϸ��̼� �����ӽ��ǵ�
	int		frameSpeed;
	//< ���� �������ϴ� ������
	int		nowFrame;
	//< ������ ����Ÿ��
	DWORD	lastTime;
	//�÷���
	bool	flag;
	bool	play;
	
}ANI_INFO,*LPANI_INFO;

enum DIR
{
	DIR_LEFT,
	DIR_RIGHT,
};

typedef struct tagUserScore
{
	unsigned int distance;
	unsigned int elapsed;
	int bonus;
} UserScore;

#endif