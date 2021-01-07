#include "stdafx.h"
#include "Object.h"

Object::Object( unsigned int id )
	:m_UID( id )
{
	//< �ؽ� ���
	m_hash = reinterpret_cast<unsigned int>(this);
}
Object::~Object( VOID )
{

}

//< ������Ʈ ���� ���̵� ���ϱ�
bool Object::isEquals( const Object &obj )
{
	if( m_hash == obj.m_hash )
	{
		return TRUE;
	}
	return FALSE;
}