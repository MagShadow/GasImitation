#pragma once

#include "stdafx.h"

class LCG 
{
public:
	LCG(uint32_t seed) : mSeed(seed) {}
	float operator()() 
	{
		mSeed = mSeed * 214013 + 2531011;
		union 
		{
			uint32_t u;
			float f;
		}
		u = { (mSeed >> 9) | 0x3F800000 };
		return u.f - 1.0f;
	}
	uint32_t ss() { return mSeed; }
private:
	uint32_t mSeed;
};