#include "stdafx.h"

CItem::CItem(RakString _instanceName, size_t _amount, float _x, float _y, float _z, size_t _id, RakString _world)
{
	id = _id;
	instanceName = _instanceName;
	amount = _amount;
	x = _x;
	y = _y;
	z = _z;
	world = _world;
};

CItem::~CItem()
{
	instanceName.FreeMemory();
};