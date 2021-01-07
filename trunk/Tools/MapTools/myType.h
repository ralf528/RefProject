#ifndef __MYTYPE_H__
#define __MYTYPE_H__
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// ☆━─ 2015.04, 전역 구조체 및 전역 타입, Ackashic. ─━☆
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

typedef struct tagAniInfo
{
	//< 애니메이션 정보 가로,세로크기
	SIZE	aniSize;
	//< 애니메이션 가로개수
	int		frameCntX;
	//< 애니메이션 세로개수
	int		frameCntY;
	//< 애니메이션 프레임스피드
	int		frameSpeed;
	//< 현재 렌더링하는 프레임
	int		nowFrame;
	//< 마지막 갱신타임
	DWORD	lastTime;
	//플래그
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