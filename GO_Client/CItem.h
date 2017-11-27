#ifndef CITEM_H
#define CITEM_H

class CItem
{
private:
	size_t id;
	zVEC3 pos;

	RakString instanceName;
	size_t amount;
	oCItem* gameItem;
public:
	CItem(RakString _instanceName, oCItem* _gameItem = NULL, size_t _amount = 1, zVEC3 _pos = zVEC3(0.0f, 0.0f, 0.0f), size_t _id = (size_t)-1);
	~CItem();

	size_t GetID() const { return this->id;};
	oCItem* GetGameItem() { return this->gameItem;};
};


#endif //CITEM_H