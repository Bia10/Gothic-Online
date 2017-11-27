#ifndef CITEM_H
#define CITEM_H

class CItem
{
private:
	size_t id;
	float x, y, z;
	RakString world;

	RakString instanceName;
	size_t amount;
public:
	CItem(RakString _instanceName, size_t _amount = 1, float _x = 0.0f, float _y = 0.0f, float _z = 0.0f, size_t _id = (size_t)-1, RakString _world = "world.ZEN");
	~CItem();

	size_t GetID() const { return this->id;};
	RakString GetInstance() const { return this->instanceName;};
	size_t GetAmount() const { return this->amount;};
	RakString GetWorldName() const { return this->world;};
	void GetPositionXYZ(float &_X, float &_Y, float &_Z){ _X = this->x; _Y = this->y; _Z = this->z;};
};

#endif //CITEM_H