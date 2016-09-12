#include <iostream>
#include <list>

class foo
{
public:
	foo(){foo::m_nNumber++;}
	~foo(){}
	void disp(void){std::cout<<"hello, i'm foo: "<<foo::m_nNumber<<std::endl;}
private:
	static int m_nNumber;
};


template<typename Object>
class SimpleObjectPool
{
public:
	SimpleObjectPool(int nMaxSize):m_nMaxSize(nMaxSize)
	{
		for(int index=0; index<m_nMaxSize; index++)
		{
			m_ObjectPool.push_back(new Object);
		}
	}
	~SimpleObjectPool()
	{
		typename std::list<Object*>::iterator iter = m_ObjectPool.begin();
		while( iter!=m_ObjectPool.end() )
		{
			delete *iter;
			++iter;
		}
		m_nMaxSize = 0;
	}
	Object* GetObject(void)
	{
		Object* pObj = NULL;
		if( m_nMaxSize<=0 )
		{
			std::cout<<"no have new object in objpool, we should new one..."<<std::endl;
			pObj = new Object();
			m_ObjectPool.push_back(pObj);
		}else{
			pObj = m_ObjectPool.front();
			m_ObjectPool.pop_front();
			m_nMaxSize--;
		}
		return pObj;
	}
	void ReturnObject(Object* pObj)
	{
		m_ObjectPool.push_back(pObj);
		m_nMaxSize++;
	}
private:
	int m_nMaxSize;
	std::list<Object*> m_ObjectPool;
};

