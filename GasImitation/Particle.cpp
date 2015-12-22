#include "Particle.h"
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <iostream>
#include "LCG.h"
#define Pi 3.14159265358979323846


using std::ostream;


Particle::Particle(double a, double b, double va, double vb)
{
	x = a;
	y = b;
	vx = va;
	vy = vb;
}

Particle::~Particle()
{
}

void Particle::initialize()
{
	static LCG RNG((unsigned)time(0));	//Ϊ��֤ÿһ�β��ظ������붨��Ϊ��̬��Ա
	static int nn = 0;
	++nn;
	num = nn;

	double v = RNG();
	double ceta = RNG() * 2 * Pi;
	vx = v*cos(ceta);
	vy = v*sin(ceta);
	
	x = RNG()*RANGE;
	y = RNG()*RANGE;
	
	//std::cout << RNG.ss() << std::endl;
	//������ɣ���������ι�����?
}

void Particle::initialize(int Rx,int Ry)
{
	static LCG RNG((unsigned)time(0));	//Ϊ��֤ÿһ�β��ظ������붨��Ϊ��̬��Ա
	static int nn = 0;
	++nn;
	num = nn;

	double v = RNG();
	double ceta = RNG() * 2 * Pi;
	vx = v*cos(ceta);
	vy = v*sin(ceta);

	x = RNG()*Rx;
	y = RNG()*Ry;

	//std::cout << RNG.ss() << std::endl;
	//������ɣ���������ι�����?
}
void Particle::stepForward(double ax, double ay, double dt)
{
	x = x + vx*dt + 0.5*ax*dt*dt;
	y = y + vy*dt + 0.5*ay*dt*dt;
	while (x < 0) x += RANGE;
	while (y < 0) y += RANGE;
	while (x >= RANGE) x -= RANGE;
	while (y >= RANGE) y -= RANGE;

	vx = vx + ax*dt;
	vy = vy + ay*dt;
	//�˴����ɣ����ڲ��õ�����򵥵�ģ���㷨��
	//��ΪRunge-Kutta������
}

void Particle::stepForward(double dt)	//�����Լ��ڲ��ļ��ٶ�ֵ
{
	x = x + vx*dt + 0.5*ax*dt*dt;
	y = y + vy*dt + 0.5*ay*dt*dt;
	while (x < 0) x += RANGE;
	while (y < 0) y += RANGE;
	while (x >= RANGE) x -= RANGE;
	while (y >= RANGE) y -= RANGE;

	vx = vx + ax*dt;
	vy = vy + ay*dt;
	//�˴����ɣ����ڲ��õ�����򵥵�ģ���㷨��
	//��ΪRunge-Kutta������
}

double Particle::Eu(Particle t)
{
	double d = sqrt((t.x_() - x)*(t.x_() - x) + (t.y_() - y)*(t.y_() - y));
	/*if (d > 1) return 0.0;
	else*/
		return (exp(-4 * d*d) - exp(-4));
	
}


ostream &operator<<(ostream& os, Particle &t)
{
	return os << '(' << t.x_() << ',' << t.y_() << ") V=(" << t.vx_() << ',' << t.vy_() << ')';
}