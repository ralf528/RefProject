#include "stdafx.h"
#include "Object.h"

Object::Object( unsigned int id )
	:m_UID( id )
{
	//< 해쉬 얻기
	m_hash = reinterpret_cast<unsigned int>(this);
}
Object::~Object( VOID )
{

}

//< 오브젝트 고유 아이디 비교하기
bool Object::isEquals( const Object &obj )
{
	if( m_hash == obj.m_hash )
	{
		return TRUE;
	}
	return FALSE;
}