#pragma once
#include "stdafx.h"

class Particle
{
public:
	Particle() = default;
	Particle(double, double, double, double);
	~Particle();

	void initialize();
	void stepForward(double, double, double);

	inline double Ek() const { return 0.5*(vx*vx + vy + vy); }
	double Eu(Particle t);

	inline double x_() const { return x; }
	inline double y_() const { return y; }
	inline double vx_() const { return vx; }
	inline double vy_() const { return vy; }
	friend std::ostream & operator<<(std::ostream &os, Particle &t);

	int f = 0;
	int num = 0;	//加入一个num作为编号器，以区别各个粒子
private:
	double x, y;
	double vx, vy;
	
};

