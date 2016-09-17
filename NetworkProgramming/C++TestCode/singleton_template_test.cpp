#include "test_code.h"
#include <string>

template<typename T> T* Singleton<T>::_instance = NULL;
//DECLARE_SINGLETON_MUMBER(T)

class GlobalVal : public Singleton<GlobalVal>
{
public:
	GlobalVal():_age(35), _name("xiakun"){}
	GlobalVal(int age, string name):_age(age), _name(name){}
	void SetAge(int age) { _age = age; }
	void SetName( string name ){ _name = name; }
	void Disp(void){cout<<"name: "<<_name<<", age: "<<_age<<endl;}
private:
	int _age;
	string _name;
};

int main(int argc, char* argv[])
{
	#define g_GlobalVal GlobalVal::GetInstance()
	
	g_GlobalVal->Disp();
	g_GlobalVal->SetAge(5);
	g_GlobalVal->SetName("xiaruncheng");
	g_GlobalVal->Disp();
	g_GlobalVal->Release();
	return 0;
}

