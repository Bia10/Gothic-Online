#include "goMath.h"

float goMath::GetDistance3D(float aX, float aY, float aZ, float bX, float bY, float bZ)
{
	float distX = aX - bX;
	float distY = aY - bY;
	float distZ = aZ - bZ;
	return sqrt(distX*distX + distY*distY + distZ*distZ);
};

float goMath::GetDistance2D(float aX, float aY, float bX, float bY)
{
	float distX = aX - bX;
	float distY = aY - bY;
	return sqrt(distX*distX + distY*distY);
};

float goMath::GetVectorAngle(float aX, float aY, float bX, float bY)
{
	float vec[3];
	if(aX == bX && aY == bY)
		vec[2] = 0;
	else
	{
		vec[0] = bX - aX;
		vec[1] = bY - aY;
		vec[2] = atan(vec[0] / vec[1]) * 180.0f / 3.14f;
		if(vec[1] < 0)
			vec[2] = vec[2] >= 180 ? vec[2] - 180 : vec[2] + 180;

	}
	return vec[2];
};

float goMath::GetNegatedAngle(float angle)
{
	float nAngle = angle - 180.0f;
	if (nAngle < 0.0f) nAngle += 360.0f;
	return nAngle;
};