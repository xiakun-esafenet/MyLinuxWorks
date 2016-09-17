#ifndef _TEST_CODE_H_
#define _TEST_CODE_H_

#include <iostream>
using namespace std;

template<typename T> 
class Singleton
{
public:
	static T* GetInstance(void);
	void Release(void);
protected:
	Singleton(){}
	~Singleton(){}
	static T* _instance;	
};

template<typename T> 
T* Singleton<T>::GetInstance(void)
{
	if( _instance==NULL )
	{
		_instance = new T;
	}

	return _instance;
}

template<typename T> 
void Singleton<T>::Release(void)
{
	if( _instance==NULL )
		return;
	delete _instance;
	_instance = NULL;
}

#define DECLARE_SINGLETON_MUMBER(_Ty) \
	template<_Ty> _Ty* Singleton<_Ty>::_instance = NULL;
#endif
