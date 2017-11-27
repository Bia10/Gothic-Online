#ifndef SKEY_H
#define SKEY_H

class SKey
{
private:
	unsigned timeLastKey;
	List<int> disabledKeys;

public:
	SKey();
	~SKey();

	void KeyEvent(int key);
	bool IsKeyEnabled(int key);
	void SetKeyEnabled(int key, bool toggle);
};

#endif //SKEY_H