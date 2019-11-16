#pragma once

class otherCharacter;

class Other_manager
{
	//< 아이디, 캐릭터 정보
	typedef std::map<char*, otherCharacter*>				other_map;
	typedef std::map<char*, otherCharacter*>::iterator		other_map_iter;
private:
	Other_manager(void);
	~Other_manager(void);

	SINGLETON( Other_manager );

public:
	//< 초기화
	bool init(void);
	//< 업데이트
	void update(void);
	//< 랜더
	void render(HDC hdc);

	//< 추가
	void addOther(char* ID, otherCharacter* other);
	//< 검색
	otherCharacter* findOther(char* ID);
	//< 삭제
	void deleteOther(char* ID);
	//< 전체 삭제
	void deleteAll(void);

	//< 메시지 받기
	void receiveMessage(char* ID, int state);

private:
	//< 아더 캐릭터 리스트
	other_map m_otherList;
};

#define OTHER_MGR Singleton<Other_manager>::getInstance()