#ifndef CVOB_H
#define CVOB_H

class CVob
{
private:
	zVEC3 rotation;
	zCVob* zVob;
	int id;
public:
	CVob(zCVob* vob, int ID);
	CVob(zSTRING& visual, zVEC3 position, zVEC3 rot, int ID);
	~CVob();

	inline zVEC3 GetRotation() { return this->rotation;};
	inline int GetID() const { return this->id;};
	inline void SetID(int ID) { this->id = ID;};
	inline zCVob* GetZVob() { return this->zVob;};
	void SetRotation(zVEC3 rot);
};

#endif //CVOB_H