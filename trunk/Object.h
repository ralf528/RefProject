#pragma once

class Object
{
public:
	//< ����ִ� ������Ʈ ��
	const static unsigned int EMPTYOBJ = UINT_MAX;
public:
	Object( unsigned int id );
	virtual ~Object( void );

	//< ������Ʈ �̸� ���
	virtual const char *toString( void ){ return "JN_Object"; }

	//< ������Ʈ ���� ���̵� ���
	inline unsigned int getUID( void ){ return m_UID; }

	//< ������Ʈ �� �Լ� 
	virtual	bool isEquals(  const Object &obj );

	//< ������Ʈ ����.
	virtual void release( void )				{ }

	//< ������Ʈ ����
	virtual void update( float fDT = 0.0f )		{ }

	//< ������Ʈ ����
	virtual void render(  HDC hdc  )			{ }

	//< ����
	virtual void		render( HDC hdc, int x , int y ) { }
	virtual void		render( HDC hdc, int x , int y, int destCX , int destCY, 
								int scrX , int srcY , int srcCX, int srcCY ) {}
private:
	//< ������Ʈ ���� Hash ��ȣ ���
	unsigned int m_hash;
	//< ������Ʈ ���� ID (�ܺο��� ����, �Ǵ� �Ŵ������� ����)
	unsigned int m_UID; //unique id
};