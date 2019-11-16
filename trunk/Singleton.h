#pragma once

//< º¹»ç ¹æÁö & ´ëÀÔ ¹æÁö
#define COPYPREVENT(type)   \
    type(const type &rhw);   \
    type& operator=(const type &rhw);

//< ½Ì±ÛÅæ ¸ÅÅ©·Î
#define SINGLETON(type)\
    COPYPREVENT(type)\
    friend Singleton<type>;

//< ½Ì±ÛÅæ ÅÛÇÃ¸´
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