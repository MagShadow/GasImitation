#include "Space.h"
#include <iomanip>
#include <cmath>
#define K 5

using namespace std;
inline void clr(int &x, int &y)
{
	while (x < 0) x += RANGE;
	while (y < 0) y += RANGE;
	while (x >= RANGE) x -= RANGE;
	while (y >= RANGE) y -= RANGE;
}
//当前的力的模型采用弹簧力,作为测试
/*double fx(double x1, double y1, double x2, double y2)
{
	return (x2 - x1)*K;
}

double fy(double x1, double y1, double x2, double y2)
{
	return (y2 - y1)*K;
}*/

//利用作用势计算真实力
double fx(double x1, double y1, double x2, double y2)
{
	double d(sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));
	if (d > 1) return 0.0; else return 8.0*exp(-4 * d*d)*(x1 - x2);
}

double fy(double x1, double y1, double x2, double y2)
{
	double d(sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));
	if (d > 1) return 0.0; else return 8.0*exp(-4 * d*d)*(y1 - y2);
}

Space::Space()
{
}

Space::Space(int n)
{
	vector<node> v1(RANGE);
	nvec.assign(RANGE, v1);
	for (int temp = 0; temp < n; ++temp)
	{
		Particle* t = new Particle;
		t->initialize();
		t->num = temp;
		nvec[t->x_()][t->y_()].push_front(t);
	}

	using namespace std;
	for (int i = 0; i < RANGE; ++i)
	{
		for (int j = 0; j < RANGE; ++j)
			cout << setw(6) << nvec[i][j].size();
		cout << endl;
	}
}


Space::~Space()
{
}

void Space::timePass(double dt)
{
	//static int times = 0;

	static double tt = 0;
	tt += dt;

	//某些黑科技，用以标记某一颗粒子有没有处理过
	cout << "Time:" << tt << endl;
	int ff = -1;
	for (int i = 0; i < RANGE; ++i)
	{
		for (int j = 0; j < RANGE;++j)
			if (!nvec[i][j].empty()) { ff = (*nvec[i][j].begin())->f; }
		if (ff != -1) break;
	}
	ff = abs(ff - 1);

	

	for (int i = 0; i < RANGE; ++i)
	{
		for (int j = 0; j < RANGE; ++j)
		{
			auto p = nvec[i][j].begin();
			double ax=0, ay=0;
			int xx, yy;

			//存储需要移动的点
			vector<int> que;	
			int que_n = 0;

			while (true)
			{
				if (p == nvec[i][j].end()) break;

				
				if ((*p)->f == ff) { ++p; continue; }
				xx = i-1; yy = j; clr(xx, yy);
				for (auto it : nvec[xx][yy])
				{
					ax += fx((*p)->x_(),(*p)->y_(), it->x_(), it->y_());
					ay += fy((*p)->x_(), (*p)->y_(), it->x_(), it->y_());
				}
				xx = i + 1; yy = j; clr(xx, yy);
				for (auto it : nvec[xx][yy])
				{
					ax += fx((*p)->x_(), (*p)->y_(), it->x_(), it->y_());
					ay += fy((*p)->x_(), (*p)->y_(), it->x_(), it->y_());
				}
				xx = i; yy = j - 1; clr(xx, yy);
				for (auto it : nvec[xx][yy])
				{
					ax += fx((*p)->x_(), (*p)->y_(), it->x_(), it->y_());
					ay += fy((*p)->x_(), (*p)->y_(), it->x_(), it->y_());
				}
				xx = i; yy = j + 1; clr(xx, yy);
				for (auto it : nvec[xx][yy])
				{
					ax += fx((*p)->x_(), (*p)->y_(), it->x_(), it->y_());
					ay += fy((*p)->x_(), (*p)->y_(), it->x_(), it->y_());
				}

				(*p)->stepForward(ax, ay, dt);
				(*p)->f = ff;
				//++times;
				if (((int)(*p)->x_() != i) || ((int)(*p)->y_() != j))
				{
					//nvec[(*p)->x_()][(*p)->y_()].push_back(*p);
					//nvec[i][j].erase(p);
					//沃日，原来问题果然在这，迭代器不能乱变，等会试试

					//cout << "No."<<(*p)->num<<" moved! (" << i << ',' << j << ")->(" << (int)(*p)->x_() << ',' << (int)(*p)->y_() << ')' << endl;
					que.push_back(que_n);
				}
				else
					++p;
				++que_n;
			}
			
			p = nvec[i][j].begin();
			int l = nvec[i][j].size();
			int jj = 0;
			for (int ii = 0; ii < l; ++ii)
			{
				if (jj >= que.size()) break;
				if (ii == que[jj])
				{
					++jj;
					//cout << "Actually (" << i << ',' << j << ")->(" << (int)(*p)->x_() << ',' << (int)(*p)->y_() << ')' << endl;
					nvec[(*p)->x_()][(*p)->y_()].push_back(*p);
					p=nvec[i][j].erase(p);
					
				}
				else
					++p;
			}
		}
	}
	
	for (int i = 0; i < RANGE; ++i)
	{
		for (int j = 0; j < RANGE; ++j)
			cout << setw(6) << nvec[i][j].size();
		cout << endl;
	}
	//cout << "Total Count:" << times << " times.\n";
}

double Space::Ek() const
{
	double sum = 0.0;
	for (int i = 0; i < RANGE; ++i)
	{
		for (int j = 0; j < RANGE; ++j)
			for (auto it : nvec[i][j]) sum += it->Ek();
		
	}
	return sum;
}

double Space::Eu()
{
	double sum = 0.0;
	int xx, yy;
	for (int i = 0; i < RANGE; ++i)
	{
		for (int j = 0; j < RANGE; ++j)
		{
			for (auto it : nvec[i][j])
			{
				auto temp = it;
				//处理本格
				for (auto it2 : nvec[i][j]) if (it!=it2) sum += it2->Eu(*temp);

				//处理相邻的格子
				xx = i - 1; yy = j; clr(xx, yy);
				for (auto it2 : nvec[xx][yy]) sum += it2->Eu(*temp);
				xx = i + 1; yy = j; clr(xx, yy);
				for (auto it2 : nvec[xx][yy]) sum += it2->Eu(*temp);
				xx = i; yy = j - 1; clr(xx, yy);
				for (auto it2 : nvec[xx][yy]) sum += it2->Eu(*temp);
				xx = i; yy = j + 1; clr(xx, yy);
				for (auto it2 : nvec[xx][yy]) sum += it2->Eu(*temp);

				//处理斜对角的格子
				xx = i - 1; yy = j - 1; clr(xx, yy);
				for (auto it2 : nvec[xx][yy]) sum += it2->Eu(*temp);
				xx = i + 1; yy = j - 1; clr(xx, yy);
				for (auto it2 : nvec[xx][yy]) sum += it2->Eu(*temp);
				xx = i - 1; yy = j + 1; clr(xx, yy);
				for (auto it2 : nvec[xx][yy]) sum += it2->Eu(*temp);
				xx = i + 1; yy = j + 1; clr(xx, yy);
				for (auto it2 : nvec[xx][yy]) sum += it2->Eu(*temp);
			}
		}

	}
	return sum*0.5;
}



