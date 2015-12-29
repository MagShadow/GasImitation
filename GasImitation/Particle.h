#pragma once
#include "stdafx.h"

class Particle
{
public:
	Particle() = default;
	Particle(double, double, double, double);
	~Particle();

	void initialize();
	void initialize(int Rx,int Ry);
	
	void setAcc(double a_x, double a_y) {  ax = a_x; ay = a_y; }
	void move(double dt);
	void veloMove(double dt);

	inline double Ek() const { return 0.5*(vx*vx + vy*vy); }
	double Eu(Particle &t);

	inline double x_() const { return x; }
	inline double y_() const { return y; }
	inline double vx_() const { return vx; }
	inline double vy_() const { return vy; }
	friend std::ostream & operator<<(std::ostream &os, Particle &t);

	int f = 0;

private:
	double x, y;
	double vx, vy;
	double ax, ay;
};

