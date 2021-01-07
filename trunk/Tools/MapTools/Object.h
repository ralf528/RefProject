#pragma once

class Object
{
public:
	//< 비어있는 오브젝트 값
	const static unsigned int EMPTYOBJ = UINT_MAX;
public:
	Object( unsigned int id );
	virtual ~Object( void );

	//< 오브젝트 이름 얻기
	virtual const char *toString( void ){ return "JN_Object"; }

	//< 오브젝트 고유 아이디 얻기
	inline unsigned int getUID( void ){ return m_UID; }

	//< 오브젝트 비교 함수 
	virtual	bool isEquals(  const Object &obj );

	//< 오브젝트 삭제.
	virtual void release( void )				{ }

	//< 오브젝트 갱신
	virtual void update( float fDT = 0.0f )		{ }

	//< 오브젝트 렌더
	virtual void render(  HDC hdc  )			{ }

	//< 렌더
	virtual void		render( HDC hdc, int x , int y ) { }
	virtual void		render( HDC hdc, int x , int y, int destCX , int destCY, 
								int scrX , int srcY , int srcCX, int srcCY ) {}
private:
	//< 오브젝트 고유 Hash 번호 얻기
	unsigned int m_hash;
	//< 오브젝트 관리 ID (외부에서 적용, 또는 매니저에서 지정)
	unsigned int m_UID; //unique id
};