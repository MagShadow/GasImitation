// GasImitation.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Particle.h"
#include "Space.h"
#include "LCG.h"
#include <list>

using namespace std;

int main()
{
	/*ofstream fout;
	fout.open("fout.txt");
	if (!fout.is_open()) { cerr << "ERROR!\n"; return 0;}*/

	Space test(100,true);
		
	for (int i = 0; i < 1000; i++)
	{
		test.timePass(0.001);
		if (i % 10 != 0) continue;
		cout << "Ek=" << test.Ek() << "  Eu=" << test.Eu() << "  E=" << test.Ek() + test.Eu() << endl;
		
	}
	
	cin.get();
	return 0;
}

//测试list
/*list<Particle*> nodet;

Particle* a[5];
for (int i = 0; i < 5; ++i)
{
a[i] = new Particle;
a[i]->initialize();
nodet.push_front(a[i]);
}

for (auto it : nodet)
{
cout << (*it) << endl;
}*/

//测试Particle类的代码
/*int n = 1;
Particle* a[5];
for (int i = 0; i < n; ++i)
{
a[i] = new Particle;
a[i]->initialize();
cout << (*a[i]) << endl;
}
double dt = 0.01;
for (int i = 0; i < 100; ++i)
{
cout << "T=" << i*dt << ':' << (*a[0]) << endl;
a[0]->stepForward(10, 5, dt);
}*/