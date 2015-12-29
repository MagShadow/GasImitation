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

inline double fx(double x1, double y1, double x2, double y2)
{
	double d(sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));
	if (d > 1) return 0.0; else return 8.0*exp(-4 * d*d)*(x1 - x2);
}

inline double fy(double x1, double y1, double x2, double y2)
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
		nvec[t->x_()][t->y_()].push_front(t);
	}
}
Space::Space(int n,bool d)
{
	vector<node> v1(RANGE);
	nvec.assign(RANGE, v1);
	for (int temp = 0; temp < n; ++temp)
	{
		Particle* t = new Particle;
		t->initialize(RANGE / 2, RANGE);
		nvec[t->x_()][t->y_()].push_front(t);
	}
}

Space::~Space()
{
}

void Space::timePass(double dt)
{
	static bool TheFirstStep(false);
		
	//ĳЩ�ڿƼ������Ա��ĳһ��������û�д����
	if (TheFirstStep) 
	{
		int ff = -1;
		for (int i = 0; i < RANGE; ++i)
		{
			for (int j = 0; j < RANGE; ++j)
				if (!nvec[i][j].empty()) { ff = (*nvec[i][j].begin())->f; }
			if (ff != -1) break;
		}
		ff = abs(ff - 1);

		for (int i = 0; i < RANGE; ++i)
		{
			for (int j = 0; j < RANGE; ++j)
			{
				auto p = nvec[i][j].begin();

				//�洢��Ҫ�ƶ��ĵ�
				vector<int> que;
				int que_n = 0;

				while (true)
				{
					if (p == nvec[i][j].end()) break;
					//��Ҳ��֪��Ϊʲô����һ��Ҫ����д����ֻ����������ͨ��

					if ((*p)->f == ff) { ++p; continue; }
					(*p)->move(dt);
					(*p)->f = ff;
					if (((int)(*p)->x_() != i) || ((int)(*p)->y_() != j)) que.push_back(que_n);
					else
						++p;
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
						nvec[(*p)->x_()][(*p)->y_()].push_back(*p);
						p = nvec[i][j].erase(p);

					}
					else
						++p;
				}
			}
		}
	}

	if (!TheFirstStep) TheFirstStep = true;
	//ֻ���ü��ٶȣ������Ȳ��ƶ�
	for (int i = 0; i < RANGE; ++i)
	{
		for (int j = 0; j < RANGE; ++j)
		{
			auto p = nvec[i][j].begin();
			
			int xx, yy;
			double ax = 0, ay = 0;

			while (p != nvec[i][j].end())
			{
				
				ax = 0; ay = 0;
				//��������ֻ���ڽ��ĸ����ӣ����б���ͶԽ��߸���
				//����
				for (auto it : nvec[i][j])
				{
					if ((*p) == it) continue;
					ax += fx((*p)->x_(), (*p)->y_(), it->x_(), it->y_());
					ay += fy((*p)->x_(), (*p)->y_(), it->x_(), it->y_());
				}

				//���ڸ�
				xx = i - 1; yy = j; clr(xx, yy);
				for (auto it : nvec[xx][yy])
				{
					ax += fx((*p)->x_(), (*p)->y_(), it->x_(), it->y_());
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

				//�ԽǸ�
				xx = i - 1; yy = j - 1; clr(xx, yy);
				for (auto it : nvec[xx][yy])
				{
					ax += fx((*p)->x_(), (*p)->y_(), it->x_(), it->y_());
					ay += fy((*p)->x_(), (*p)->y_(), it->x_(), it->y_());
				}
				xx = i + 1; yy = j - 1; clr(xx, yy);
				for (auto it : nvec[xx][yy])
				{
					ax += fx((*p)->x_(), (*p)->y_(), it->x_(), it->y_());
					ay += fy((*p)->x_(), (*p)->y_(), it->x_(), it->y_());
				}
				xx = i - 1; yy = j + 1; clr(xx, yy);
				for (auto it : nvec[xx][yy])
				{
					ax += fx((*p)->x_(), (*p)->y_(), it->x_(), it->y_());
					ay += fy((*p)->x_(), (*p)->y_(), it->x_(), it->y_());
				}
				xx = i + 1; yy = j + 1; clr(xx, yy);
				for (auto it : nvec[xx][yy])
				{
					ax += fx((*p)->x_(), (*p)->y_(), it->x_(), it->y_());
					ay += fy((*p)->x_(), (*p)->y_(), it->x_(), it->y_());
				}
				(*p)->setAcc(ax, ay);
				(*p)->veloMove(dt);
				++p;				
			}
		}
	}
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
				//������
				for (auto it2 : nvec[i][j]) if (it != it2) sum += it2->Eu(*temp);

				//�������ڵĸ���
				xx = i - 1; yy = j; clr(xx, yy);
				for (auto it2 : nvec[xx][yy]) sum += it2->Eu(*temp);
				xx = i + 1; yy = j; clr(xx, yy);
				for (auto it2 : nvec[xx][yy]) sum += it2->Eu(*temp);
				xx = i; yy = j - 1; clr(xx, yy);
				for (auto it2 : nvec[xx][yy]) sum += it2->Eu(*temp);
				xx = i; yy = j + 1; clr(xx, yy);
				for (auto it2 : nvec[xx][yy]) sum += it2->Eu(*temp);

				//����б�Խǵĸ���
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

vector<int> Space::dis_x()
{
	vector<int> dis(501, 0);
	for (int i = 0; i < RANGE; ++i)
	{
		for (int j = 0; j < RANGE; ++j)
			for (auto it : nvec[i][j]) ++dis[(int)((it->x_()) / 0.4)];
	}
	return dis;
}

vector<int> Space::dis_v()
{
	vector<int> dis(501, 0);
	double v;
	for (int i = 0; i < RANGE; ++i)
	{
		for (int j = 0; j < RANGE; ++j)
			for (auto it : nvec[i][j])
			{
				v = sqrt(it->vx_()*it->vx_() + it->vy_()*it->vy_());
				if (v >= 5) continue;
				++dis[int(v * 100)];
			}
	}
	return dis;
}