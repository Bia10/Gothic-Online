#ifndef CITEMMANAGER_H
#define CITEMMANAGER_H

#define itemManager CItemManager::GetManager()

class CItem;

class CItemManager
{
private:
	CItemManager();
	CItemManager( const CItemManager & ) {};
	~CItemManager();
public:
	List<CItem*> itemList;
	static CItemManager & GetManager()
	{
		static CItemManager manager;
		return manager;
	}
	unsigned int GetNumberOfItems()
	{
		return this->itemList.Num();
	}
	bool GetFreeID(unsigned int& itemID);

	CItem* CreateItem(RakString instance, unsigned int amount, float x, float y, float z, RakString world);
	bool DestroyItem(unsigned int _itemID);

	bool CreateItemForPlayer(CItem* item, CPlayer* player);
	bool DestroyItemForPlayer(CItem* item, CPlayer* player);

	CItem* GetItem(unsigned int _itemID);

};

#endif //CITEMMANAGER_H