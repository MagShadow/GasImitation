// GasImitation.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Particle.h"
#include "Space.h"
#include "LCG.h"
#include <list>

using namespace std;

void ctx(Space &test, ofstream &ff);
void ctv(Space &test, ofstream &ff);

int main()
{
	/*ofstream fout1;
	fout1.open("Ek.txt");
	if (!fout1.is_open()) { cerr << "ERROR!\n"; return 0; }

	ofstream fout2;
	fout2.open("Eu.txt");
	if (!fout2.is_open()) { cerr << "ERROR!\n"; return 0; }

	ofstream fout;
	fout.open("E.txt");
	if (!fout.is_open()) { cerr << "ERROR!\n"; return 0; }*/

	ofstream ff1;
	ff1.open("Dis_loc_whole.txt");
	if (!ff1.is_open()) { cerr << "ERROR!\n"; return 0; }

	ofstream ff2;
	ff2.open("Dis_velo_whole.txt");
	if (!ff2.is_open()) { cerr << "ERROR!\n"; return 0; }

	cout << "Input N:\n";
	int nn;
	cin >> nn;

	Space test(nn);
	// 两参数代表半空间，单参数表示全空间

	cout << "Input times:\n";
	int times;
	cin >> times;

	ctx(test,ff1);
	ctv(test,ff2);

	//double ek, eu, e;
	for (int i = 0; i < times*5; i++)
	{
		test.timePass(0.02);
		cout << i << ' ';
		if (i % 5 != 4) continue;
		//ek = test.Ek();
		//eu = test.Eu();
		//e = ek + eu;
		/*fout1 << ek << endl;
		fout2 << eu << endl;
		fout << e << endl;*/
		cout << "Time:" << (i + 1)*0.02 << endl;

		if ((i == 39) || (i == 74) || (i==114)||(i==149)) { ctx(test, ff1); ctv(test, ff2); }
		
		//cout << "Ek=" << test.Ek() << "  Eu=" << test.Eu() << "  E=" << test.Ek() + test.Eu() << endl;
		
	}
	cout << "Mission Complete!" << endl;
	/*fout.close();
	fout1.close();
	fout2.close();*/
	cin.get();
	return 0;
}

void ctx(Space & test, ofstream & ff)
{
	ff << "Begin of the X-Distribution.\n";
	vector<int>& dis = test.dis_x();
	for (int i = 0; i < 500; ++i) ff << dis[i] << endl;
	ff << "End of the X-Distribution.\n";

}

void ctv(Space & test, ofstream & ff)
{
	ff << "Begin of the V-Distribution.\n";
	vector<int>& dis = test.dis_v();
	for (int i = 0; i < 500; ++i) ff << dis[i] << endl;
	ff << "End of the V-Distribution.\n";
}
