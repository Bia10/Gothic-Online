#ifndef _ZGOVOB_H
#define _ZGOVOB_H
#include "zcvob.h"

class zGOVob : public zCVob
{
private:
	zVEC3 goRotation;
public:
	zVEC3 GetRotation(){ return (&this->goRotation != NULL) ? this->goRotation : zVEC3(0.0f,0.0f,0.0f); }
	void GetRotation(float &x, float &y, float &z)
	{
		if( &this->goRotation != NULL )
		{
			x = this->goRotation.x;
			y = this->goRotation.y;
			z = this->goRotation.z;
		}
		else
		{
			x, y, z = 0.0f;
		}
	}
	void SetRotation(zVEC3& rot)
	{
		this->goRotation = rot;
		reinterpret_cast<zCVob*>(this)->SetRotation(rot);
	};
	void SetRotation(float x, float y, float z)
	{
		this->SetRotation(zVEC3(x,y,z));
	}
};
#endif _ZGOVOB_H