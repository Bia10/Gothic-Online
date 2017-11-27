#ifndef CITEMMANAGER_H
#define CITEMMANAGER_H

#define itemManager CItemManager::GetManager()

class CItem;

class CItemManager
{
private:
	CItemManager();
	~CItemManager();
	CItemManager( const CItemManager& ){};
public:
	List<CItem*> itemList;
	static CItemManager & GetManager()
	{
		static CItemManager manager;
		return manager;
	}
	size_t GetNumberOfItems()
	{
		return this->itemList.Num();
	}

	oCItem* CreateItem(RakString _itemInstance, zVEC3 _pos, size_t _amount, size_t _itemID);
	bool DestroyItem(size_t _itemID);

	bool IsItemExist(size_t _itemID);

	bool SendDropItem(RakString _itemInstance, zVEC3 _pos, size_t _amount);
	bool SendTakeItem(oCItem* item);

	CItem* GetItem(oCItem* _item);
	CItem* GetItem(size_t _itemID);
};

#endif //CITEMMANAGER_H