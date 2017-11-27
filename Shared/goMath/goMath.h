#ifndef _GO_MATH_H
#define _GO_MATH_H

#include <math.h>

namespace goMath
{
	float GetDistance3D(float aX, float aY, float aZ, float bX, float bY, float bZ);
	float GetDistance2D(float aX, float aY, float bX, float bY);
	float GetVectorAngle(float aX, float aY, float bX, float bY);
	float GetNegatedAngle(float angle);
};


#endif //_GO_MATH_H