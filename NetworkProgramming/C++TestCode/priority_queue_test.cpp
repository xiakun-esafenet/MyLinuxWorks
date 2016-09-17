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
//������ȶ��е�Ԫ���ǽṹ������࣬��������<��ʵ�ֱȽ�(ע�����ص���<������>)
//��������trueΪ���ѣ�����falseΪ��С��
//���Ҫʵ����С�ѣ�ע��Ƚ�ʹ�õ���>��
	friend bool operator<(const UserInfo& ui1, const UserInfo& ui2){ return ui1._age>ui2._age;}

//ע�������÷�����Ϊ������os������Ϊconst, ����ֵ���ԣ�
	friend const ostream& operator<<(ostream& os, const UserInfo& ui)
	{
		os<<"name: "<<ui._name<<", age: "<<ui._age<<endl;
		return os;
	}
private:
	string _name;
	int _age;
};

//������ȶ��е�Ԫ�ز��ǽṹ�����ͣ������ͨ������()����������ʽ���������ȶ���
//��ȻԪ���ǽṹ�����͵ģ�Ҳ����ͨ������()���������������ȼ�����һ�������ڽṹ��������<
class mycmp
{
public:
	bool operator()(const UserInfo& u1, const UserInfo& u2) const
	{
		//ע�⣬const ����ֻ�ܵ���const ���������GetAge��������Ϊconst����
		//����һ�������εģ�������ע�������
		return u1.GetAge() > u2.GetAge();
	}
};
int main(int argc, char* argv[])
{
	//�ṹ��������operator<���������¶������ȶ���
	priority_queue<UserInfo> pq_ui;

	//ʹ�ú�������(����operator()������Ķ���)�����¶������ȶ���
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
