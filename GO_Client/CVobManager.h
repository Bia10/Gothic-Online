#ifndef CVOBMANAGER_H
#define CVOBMANAGER_H

#define vobManager CVobManager::GetManager()


class CVob;
class CVobManager
{
private:
	CVobManager();
	CVobManager( const CVobManager & ) {};
	~CVobManager();

	size_t GetFreeID();
public:
	static CVobManager& GetManager()
	{
		static CVobManager manager;
		return manager;
	}

	List<CVob*> vobList;

	size_t GetNumberOfVobs()
	{
		return this->vobList.Num();
	}

	CVob* CreateVob(zSTRING& visual, zVEC3 position, zVEC3 rot);
	bool DestroyVob(CVob* vob);
	CVob* GetById(int ID);
	CVob* GetByPosition(zVEC3 position);
	
};

#endif //CVOBMANAGER_H