#include <vector>
#include <iostream>
#include <queue>
#include <string>

using namespace std;

class UserInfo
{
public:
	UserInfo(){}
	UserInfo(string name, int age):_name(name), _age(age){}
	int GetAge(void) const { return _age; }
//如果优先队列的元素是结构体或者类，可以重载<来实现比较(注意重载的是<，而非>)
//函数返回true为最大堆，返回false为最小堆
//因此要实现最小堆，注意比较使用的是>号
	friend bool operator<(const UserInfo& ui1, const UserInfo& ui2){ return ui1._age>ui2._age;}

//注意这种用法，作为参数的os不可以为const, 返回值可以，
	friend const ostream& operator<<(ostream& os, const UserInfo& ui)
	{
		os<<"name: "<<ui._name<<", age: "<<ui._age<<endl;
		return os;
	}
private:
	string _name;
	int _age;
};

//如果优先队列的元素不是结构体类型，则可以通过重载()操作符的形式来定义优先队列
//当然元素是结构体类型的，也可以通过重载()操作符来定义优先级，不一定必须在结构体内重载<
class mycmp
{
public:
	bool operator()(const UserInfo& u1, const UserInfo& u2) const
	{
		//注意，const 对象只能调用const 方法，因此GetAge函数必须为const函数
		//这是一个很隐蔽的，不容易注意的问题
		return u1.GetAge() > u2.GetAge();
	}
};
int main(int argc, char* argv[])
{
	//结构体内重载operator<方法后，如下定义优先队列
	priority_queue<UserInfo> pq_ui;

	//使用函数对象(重载operator()函数后的对象)后，如下定义优先队列
	//priority_queue<UserInfo, vector<UserInfo>, mycmp> pq_ui;

	pq_ui.push(UserInfo("xiakun", 35));
	pq_ui.push(UserInfo("xiaruncheng", 5));
	pq_ui.push(UserInfo("limo", 32));

	while( pq_ui.empty()==false )
	{
		cout<<pq_ui.top();
		pq_ui.pop();
	}

	return 0;
}
