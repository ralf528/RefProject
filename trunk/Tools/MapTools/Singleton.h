#pragma once

//< ��������� ���Թ���
#define COPYPREVENT(type)  \
	type( const type &rhw );   \
	type& operator=( const type &rhw );

//< �̱��� ��ũ��
#define SINGLETON(type)\
	COPYPREVENT(type)\
	friend Singleton<type>;


//< �̱��� ���ø�
template <typename T>
class Singleton
{
private:
	Singleton(void) {}
	~Singleton(void) {}

	//< �ܺ� �������̽� 
public:
	static T*	getInstance( void );
};

template <typename T>
T*	Singleton<T>::getInstance( void )
{
	static T instance;
	return &instance;
}

