#ifndef _SINGLETON_H_
#define _SINGLETON_H_

template<typename T>
class Singleton
{
public:
	static inline T* GetInstance(void);
	void Release(void);
protected:
	Sigleton(){}
	~Sigleton(){}
	static T* _instance;
};

template<typename T> 
T* Singleton<T>::GetInstance(void)
{
	if( _instance==NULL )
		_instance = new T;
	return _instance;
}

template<typename T>
void Singleton<T>::Release(void)
{
	if( _instance==NULL )
		return;
	
	delete _instance;
	_instance = NULL;

	return;
}

#define DECLARE_SINGLETON_MUMBER(_Ty)	\
	template<typename _Ty> _Ty* Singleton<_Ty>::_instance = NULL;


#endif

