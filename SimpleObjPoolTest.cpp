#include "SimpleObjPoolTest.h"

int foo::m_nNumber = 0;

int main(int argc, char* argv[])
{
	SimpleObjectPool<foo> objPool(3);

	foo* fp1 = objPool.GetObject();
	fp1->disp();
	foo* fp2 = objPool.GetObject();
	foo* fp3 = objPool.GetObject();
	foo* fp4 = objPool.GetObject();
	fp4->disp();
	return 0;
}

