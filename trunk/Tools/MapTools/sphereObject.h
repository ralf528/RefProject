#pragma once

class ImageNode;

//마법 구체
class sphereObject
{
public:
	//생성자 소멸자
	sphereObject(void);
	~sphereObject(void);

public:
	//< 인터페이스	
	//초기화
	bool init(void);
	//해제
	void release(void);
	//업데이트
	void update(void);
	//그리기
	void render(HDC hdc);

	//발사
	void shoot( POINT &startPoint, int dir );
	//

	//위치 설정
	void setPos(POINT pos);
	void setPos(LONG x, LONG y);
	//위치 리턴
	POINT getPos(void) { return m_pos; }

private:
	//< 내부 함수
	//렉트 설정
	void setRect(void);

private:
	//발사된 위치
	POINT m_startPos;
	//현재 위치
	POINT m_pos;
	RECT m_rect;
	//살아있는지
	bool m_flag;
	//방향
	int m_dir;
	//속도
	int m_speed;
	
	//이미지
	ImageNode *m_img;
};