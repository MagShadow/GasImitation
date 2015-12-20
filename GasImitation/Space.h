#pragma once
#include <vector>
#include <list>
#include "Particle.h"

using std::vector;
using std::list;

typedef  list<Particle*> node;

class Space
{
public:
	Space();
	Space(int n);
	~Space();

	void timePass(double dt);

	double Ek() const;
	double Eu();

private:
	vector<vector<node>> nvec;
};

