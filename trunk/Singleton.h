#pragma once

//< ���� ���� & ���� ����
#define COPYPREVENT(type)   \
    type(const type &rhw);   \
    type& operator=(const type &rhw);

//< �̱��� ��ũ��
#define SINGLETON(type)\
    COPYPREVENT(type)\
    friend Singleton<type>;

//< �̱��� ���ø�
template <typename T>
class Singleton
{
private:
    Singleton() {}
    ~Singleton() {}

public:
    static T* GetInstance();
};

template <typename T>
T* Singleton<T>::GetInstance()
{
    static T instance;
    return &instance;
}